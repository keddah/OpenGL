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

	vertexPosIndex = shader.GetAttribute("vertexPos");

	if (vertexPosIndex == -1)
	{
		print("Couldn't get shader attribute - Vertex Position")
		print(glGetError())
		return;
	}

	model_matrix_address = glGetUniformLocation(shader.GetID(), "modelMatrix");
	view_matrix_address = glGetUniformLocation(shader.GetID(), "viewMatrix");
	projection_matrix_address = glGetUniformLocation(shader.GetID(), "projectionMatrix");

	if(model_matrix_address == -1 || view_matrix_address == -1 || projection_matrix_address == -1)
	{
		print("One or more of the matrix uniforms weren't found...")
		return;
	}

	// Initialise the vertices after the shaders.
	baManager = new BufferArrayManager(vertices, indices);
	mat = new Material(shader);
	for(int i = 0; i < 5; i++) mat->NewTexture("df");
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

    glUniformMatrix4fv(model_matrix_address, 1, GL_FALSE, value_ptr(modelMatrix));
    glUniformMatrix4fv(view_matrix_address, 1, GL_FALSE, value_ptr(rCam.GetViewMatrix()));
    glUniformMatrix4fv(projection_matrix_address, 1, GL_FALSE, value_ptr(rCam.GetProjectionMatrix()));
	
    // glUnifrom used to set values on the GPU
	// shader.SetVec4Attrib("colour", 0, .2f, .45f, 1);


	mat->BindTexture();
	baManager->BindVBuffer();
	baManager->BindIBuffer();

	// Stride = all the compCounts added together
	// Returns the component count so that the offset can be calculated automatically
	GLuint compCount = baManager->SetArrayAttrib(0, 3, GL_FLOAT, 9 * sizeof(GLfloat), nullptr);		// Position
	compCount = baManager->SetArrayAttrib(1, 4, GL_FLOAT, 9 * sizeof(GLfloat), reinterpret_cast<void*>(compCount * sizeof(GLfloat))) + compCount;		// Colour
	baManager->SetArrayAttrib(2, 2, GL_FLOAT, 9 * sizeof(GLfloat), reinterpret_cast<void*>(compCount * sizeof(GLfloat)));		// Tex Coordinates

    glDrawElements(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_INT, NULL);
	
    glDisableVertexAttribArray(vertexPosIndex);
	baManager->UnbindAll();
	mat->UnbindTexture();
	
	shader.Deactivate();
}

void Mesh::UpdateVertices()
{
	shader.SetVec3Attrib("vertexPos", transform.position);

	vertexPosIndex = shader.GetAttribute("vertexPos");
}