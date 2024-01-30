#include "Mesh.h"

Mesh::Mesh(const std::vector<GLfloat>& _vertices, const std::vector<GLuint>& _indices, Camera& camera) : rCam(camera)
{
	vertices = _vertices;
	indices = _indices;
	std::vector<glm::vec4> colours = {{0, .2f, .6f, 1}};
	
	float x, y, z;
	for(int i = 0; i < vertices.size(); i++)
	{
		if(i % 1 == 0) x = vertices[i];
		else if(i % 2 == 0) y = vertices[i];
		else if(i % 3 == 0) z = vertices[i];
		
		else
		{
			Vertex v = {{x, y, z}, colours[i]};
			// vertexes.emplace_back(v);
		}
	}
	
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

	// Initialise the vertices after the shaders.
	baManager = new BufferArrayManager(vertices, indices);
}

void Mesh::Update(float deltaTime)
{
	transform.rotation.x += .000001f;
	transform.rotation.z += .000001f;
	// transform.position.y += .00001f;
}

void Mesh::Render() const
{
	if(!visible) return;
	
    glUseProgram(shader.GetID());

    glm::mat4 modelMatrix = glm::mat4(1);
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
	shader.SetVec4Attrib("fragColour", 0, .2f, .45f, 1);


	baManager->BindVBuffer();
	baManager->BindIBuffer();
    glVertexAttribPointer(vertexPosIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(vertexPosIndex);
	
    glDrawElements(GL_TRIANGLE_FAN, vertices.size(), GL_UNSIGNED_INT, NULL);
	
    glDisableVertexAttribArray(vertexPosIndex);
	baManager->UnbindAll();
	
    glUseProgram(NULL);
}

void Mesh::UpdateVertices()
{
	shader.SetVec3Attrib("vertexPos", transform.position);

	vertexPosIndex = shader.GetAttribute("vertexPos");
}