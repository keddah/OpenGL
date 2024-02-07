#include "Mesh.h"
#include <gtx/quaternion.hpp>
#include <gtx/string_cast.hpp>

Mesh::Mesh(const std::vector<GLfloat>& vertexData, const std::vector<GLuint>& _indices)
{
	indices = _indices;
	
	float x, y, z;
	float u, v;

	// Loop through each set of vertex data
	for (int i = 0; i < vertexData.size(); i += 5)
	{
		x = vertexData[i];
		y = vertexData[i + 1];
		z = vertexData[i + 2];

		u = vertexData[i + 3];
		v = vertexData[i + 4];

		Vertex newVertex;
		newVertex.position[0] = x;
		newVertex.position[1] = y;
		newVertex.position[2] = z;
		
		newVertex.colour[0] = 1;
		newVertex.colour[1] = 1;
		newVertex.colour[2] = 1;
		newVertex.colour[3] = 1;
		
		newVertex.texCoords[0] = u;
		newVertex.texCoords[1] = v;
		vertices.emplace_back(newVertex);
	}
	
	InitShaders();
	
	CalculateAABoundingBox();
}

void Mesh::InitShaders()
{
	shader.Init();

	vertArrayIndex = shader.GetAttribute("vertexPos");

	if (vertArrayIndex == -1)
	{
		print("Couldn't get shader attribute - Vertex Position")
		print(glGetError())
		return;
	}

	// Initialise the vertices after the shaders.
	baManager = new BufferArrayManager(GetVertexData(), indices);
	mat = new Material(shader);
}

void Mesh::CalculateAABoundingBox()
{
	glm::vec3 minBounds = glm::vec3(std::numeric_limits<float>::max());
	glm::vec3 maxBounds = glm::vec3(std::numeric_limits<float>::lowest());

	// Convert Euler angles to quaternion
	const glm::quat rotationQuat = glm::quat(transform.rotation);

	// For each set of vertex data 
	for (const auto& vert : vertices)
	{
		// Create a vector3 of the position of each set of vertex data
		glm::vec3 vertex(vert.position[0], vert.position[1], vert.position[2]);

		// Apply rotation to each vertex position
		vertex = rotationQuat * vertex;

		// Apply scale to each vertex position
		vertex *= transform.scale;
		
		// Apply translation to each vertex position
		vertex += transform.position;
		

		// Update minBounds and maxBounds
		minBounds = min(minBounds, vertex);
		maxBounds = max(maxBounds, vertex);

	}

	boundingBox = { minBounds, maxBounds, (minBounds + maxBounds) * 0.5f };
}


void Mesh::Render(Camera* cam) const
{
	if(!visible) return;

	shader.Activate();

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = translate(modelMatrix, transform.position);

	if (!looking)
	{
		modelMatrix = rotate(modelMatrix, static_cast<float>(transform.rotation.x * 180 / std::_Pi), { 1,0,0 });
		modelMatrix = rotate(modelMatrix, static_cast<float>(transform.rotation.y * 180 / std::_Pi), { 0,1,0 });
		modelMatrix = rotate(modelMatrix, static_cast<float>(transform.rotation.z * 180 / std::_Pi), { 0,0,1 });
	}

    modelMatrix = scale(modelMatrix, transform.scale);

    cam->UpdateViewMatrix();

	shader.SetMat4Attrib("modelMatrix", looking? rotMatrix : modelMatrix);
	shader.SetMat4Attrib("viewMatrix", cam->GetViewMatrix());
	shader.SetMat4Attrib("projectionMatrix", cam->GetProjectionMatrix());
	
	// shader.SetVec4Attrib("colour", 0, .2f, .45f, 1);

	baManager->BindArray();
	baManager->BindVBuffer();
	baManager->BindIBuffer();
	if(mat) mat->BindTexture();

	// Stride = all the compCounts added together
	constexpr GLsizei stride =  sizeof(Vertex);
	
	// Using sizeof(Vertex) produces 96 ... That value is higher than it needs to be
	baManager->SetArrayAttrib(0, Vertex::PositionCount(), GL_FLOAT, stride, nullptr);	// Position
	baManager->SetArrayAttrib(1, Vertex::ColourCount(), GL_FLOAT, stride, reinterpret_cast<void*>(sizeof(Vertex::position)));	// Colour
	baManager->SetArrayAttrib(2, Vertex::TexCoordsCount(), GL_FLOAT, stride, reinterpret_cast<void*>(sizeof(Vertex::colour) + sizeof(Vertex::position)));	// TexCoords

    glCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL));
	
	glCall(glDisableVertexAttribArray(vertArrayIndex));
	baManager->UnbindAll();
	if(mat) mat->UnbindTexture();
	
	shader.Deactivate();
}

void Mesh::LookAtRotation(const glm::mat4 matrix)
{
	rotMatrix = matrix;
	looking = true;
}
