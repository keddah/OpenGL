#include "Mesh.h"

Mesh::Mesh(const std::vector<GLfloat>& _vertices, const std::vector<GLuint>& _indices, Camera& camera) : rCam(camera)
{
	vertices = _vertices;
	indices = _indices;
	
	// float x, y, z;
	// for(int i = 0; i < vertices.size(); i++)
	// {
	// 	if(i % 1 == 0) x = vertices[i];
	// 	else if(i % 2 == 0) y = vertices[i];
	// 	else if(i % 3 == 0) z = vertices[i];
	// 	
	// 	else
	// 	{
	// 		Vertex v = {{x, y, z}};
	// 		vertexes.emplace_back(v);
	// 	}
	// }
	
    // If shader initialisation was successful, init the vertices.
    InitShaders();
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
	baManager = new BufferArrayManager(vertices, indices);
	mat = new Material(shader);
}

void Mesh::Update(float deltaTime)
{
	transform.rotation.x += .005f * deltaTime;
	transform.rotation.z += .005f * deltaTime;
	// transform.position.y += .00001f;
}

void Mesh::Render() const
{
	if(!visible) return;

	shader.Activate();

    glm::mat4 modelMatrix {1};
    modelMatrix = rotate(modelMatrix, static_cast<float>(transform.rotation.x * 180 / std::_Pi), {1,0,0});
    modelMatrix = rotate(modelMatrix, static_cast<float>(transform.rotation.y * 180 / std::_Pi), {0,1,0});
    modelMatrix = rotate(modelMatrix, static_cast<float>(transform.rotation.z * 180 / std::_Pi), {0,0,1});
	
	modelMatrix = translate(modelMatrix, transform.position);
	
    modelMatrix = scale(modelMatrix, transform.scale);

    rCam.UpdateViewMatrix();

	shader.SetMat4Attrib("modelMatrix", modelMatrix);
	shader.SetMat4Attrib("viewMatrix", rCam.GetViewMatrix());
	shader.SetMat4Attrib("projectionMatrix", rCam.GetProjectionMatrix());
	
	// shader.SetVec4Attrib("colour", 0, .2f, .45f, 1);

	baManager->BindVBuffer();
	baManager->BindIBuffer();
	mat->BindTexture();

	// Stride = all the compCounts added together
	// Returns the component count so that the offset can be calculated automatically
	GLuint compCount = baManager->SetArrayAttrib(0, 3, GL_FLOAT, 9 * sizeof(GLfloat), nullptr);		// Position
	compCount = baManager->SetArrayAttrib(1, 4, GL_FLOAT, 9 * sizeof(GLfloat), reinterpret_cast<void*>(compCount * sizeof(GLfloat))) + compCount;		// Colour
	baManager->SetArrayAttrib(2, 2, GL_FLOAT, 9 * sizeof(GLfloat), reinterpret_cast<void*>(compCount * sizeof(GLfloat)));		// Tex Coordinates

    glCall(glDrawElements(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_INT, NULL));
	
	glCall(glDisableVertexAttribArray(vertArrayIndex));
	baManager->UnbindAll();
	mat->UnbindTexture();
	
	shader.Deactivate();
}
