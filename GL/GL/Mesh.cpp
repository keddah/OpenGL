/**************************************************************************************************************
* Mesh - Code
*
* Creates a vector of the Vertex struct from the supplied data from its constructor. Responsible for drawing the information to the screen
* by creating several matrices. Responsible for updating its own bounding box from its transform which can be set by other classes.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#include "Mesh.h"
#include <gtx/quaternion.hpp>
#include <gtx/string_cast.hpp>

Mesh::Mesh(const std::vector<GLfloat>& vertexData, const std::vector<GLuint>& _indices, const std::vector<std::string>& materialPath)
{
	indices = _indices;
	
	// Loop through each set of vertex data
	for (int i = 0; i < vertexData.size(); i += Vertex::GetCount())
	{
		const float x = vertexData[i];
		const float y = vertexData[i + 1];
		const float z = vertexData[i + 2];
		
		const float nR = vertexData[i + 3];
		const float nG = vertexData[i + 4];
		const float nB = vertexData[i + 5];
		
		const float u = vertexData[i + 6];
		const float v = vertexData[i + 7];

		Vertex newVertex;
		newVertex.position[0] = x;
		newVertex.position[1] = y;
		newVertex.position[2] = z;
		
		newVertex.normals[0] = nR;
		newVertex.normals[1] = nG;
		newVertex.normals[2] = nB;
		
		newVertex.texCoords[0] = u;
		newVertex.texCoords[1] = v;
		vertices.emplace_back(newVertex);
	}
	
	Init(materialPath);

	
	CalculateAABoundingBox();
}

void Mesh::Init(const std::vector<std::string>& matPath)
{
	// Initialise the vertices after the shaders.
	baManager = new BufferArrayManager(GetVertexData(), indices);
	mat = new Material(matPath);
	
	vertArrayIndex = mat->GetShader().GetAttribute("vertexPos");

	if (vertArrayIndex == -1)
	{
		print("Couldn't get shader attribute - Vertex Position")
		print(glGetError())
	}

}

void Mesh::CalculateAABoundingBox()
{
	glm::vec3 minBounds = glm::vec3(std::numeric_limits<float>::max());
	glm::vec3 maxBounds = glm::vec3(std::numeric_limits<float>::lowest());

	for (const auto& vert : vertices)
	{
		glm::vec3 vertex = vert.GetPositionVec();

		// Apply scaling
		vertex.x *= transform.scale.x;
		vertex.y *= transform.scale.y;
		vertex.z *= transform.scale.z;

		// Apply rotation
		// glm::quat rotationQuat = glm::quat(transform.rotation);
		// vertex = rotationQuat * vertex;

		// Apply translation
		vertex += transform.position;

		// Update minBounds and maxBounds
		minBounds = glm::min(minBounds, vertex);
		maxBounds = glm::max(maxBounds, vertex);
	}

	minBounds += bbOffset;
	maxBounds += bbOffset;
	boundingBox = { minBounds, maxBounds, (minBounds + maxBounds) * 0.5f };
}



void Mesh::Lighting(const Camera* cam, const Light& light) const
{
	const Shader& shader = mat->GetShader();
	shader.SetFloatAttrib("intensity", light.GetIntensity());
	shader.SetVec3Attrib("lightPos", light.GetPosition());
	shader.SetVec3Attrib("lightColour", light.GetColour());
	shader.SetVec3Attrib("camPos", cam->GetPosition());
}

void Mesh::Render(const Camera* cam, const Light& light) const
{
	debugger.BoundingBoxDebug(cam, transform.position, boundingBox);
	
	if(!visible) return;
	const Shader& shader = mat->GetShader();

	shader.Activate();
		
	Lighting(cam, light);

	glm::mat4 modelMatrix = glm::mat4(1);

	if (!looking)
	{
		modelMatrix = translate(modelMatrix, transform.position);
		
		modelMatrix = rotate(modelMatrix, static_cast<float>(transform.rotation.x * 180 / std::_Pi), { 1,0,0 });
		modelMatrix = rotate(modelMatrix, static_cast<float>(transform.rotation.y * 180 / std::_Pi), { 0,1,0 });
		modelMatrix = rotate(modelMatrix, static_cast<float>(transform.rotation.z * 180 / std::_Pi), { 0,0,1 });
		
		modelMatrix = scale(modelMatrix, transform.scale);
	}

	shader.SetMat4Attrib("modelMatrix", looking? rotMatrix : modelMatrix);
	shader.SetMat4Attrib("viewMatrix", cam->GetViewMatrix());
	shader.SetMat4Attrib("projectionMatrix", cam->GetProjectionMatrix());


	baManager->BindArray();
	baManager->BindVBuffer();
	baManager->BindIBuffer();
	if(mat)
	{
		mat->BindTextures(0);
		mat->BindTextures(1);
	}

	// Stride = all the compCounts added together
	constexpr GLsizei stride = sizeof(Vertex);
	
	// Using sizeof(Vertex) produces 96 ... That value is higher than it needs to be
	baManager->SetArrayAttrib(0, Vertex::PositionCount(), GL_FLOAT, stride, nullptr);	// Position
	baManager->SetArrayAttrib(1, Vertex::NormalCount(), GL_FLOAT, stride, (void*)offsetof(Vertex, normals));	// Colour
	baManager->SetArrayAttrib(2, Vertex::TexCoordsCount(), GL_FLOAT, stride, (void*)offsetof(Vertex, texCoords));	// TexCoords

    glCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL));
	
	glCall(glDisableVertexAttribArray(vertArrayIndex));
	baManager->UnbindAll();
	if(mat) mat->UnbindTextures();
	
	shader.Deactivate();
}

void Mesh::LookAtRotation(const glm::mat4& matrix)
{
	rotMatrix = translate(rotMatrix, transform.position);
	rotMatrix = matrix;
	rotMatrix = scale(rotMatrix, transform.scale);


	looking = true;
}

void Mesh::CreateMaterial(const std::vector<std::string>& texturePaths)
{
	delete mat;

	mat = new Material(texturePaths);
}
