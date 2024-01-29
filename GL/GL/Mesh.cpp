#include "Mesh.h"

Mesh::Mesh(const std::vector<GLfloat>& _vertices, const std::vector<GLuint>& _indices, Camera& camera) : rCam(camera)
{
	vertices = _vertices;
	indices = _indices;
	
    // If shader initialisation was successful, init the vertices.
    if(InitShaders()) InitVertices();
}

void Mesh::InitVertices()
{
	// The vertex buffer (positions of all the vertices)
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	// The index buffer (the correlation between the vertices)
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(0);
}

bool Mesh::InitShaders()
{
	shader.Init();

	vertexPosIndex = shader.GetAttribute("vertexPos");

	if (vertexPosIndex == -1)
	{
		print("Couldn't get shader attribute - Vertex Position")
		print(glGetError())
		return false;
	}

	model_matrix_address = glGetUniformLocation(shader.GetID(), "modelMatrix");
	view_matrix_address = glGetUniformLocation(shader.GetID(), "viewMatrix");
	projection_matrix_address = glGetUniformLocation(shader.GetID(), "projectionMatrix");
	
	return true;
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
    const GLint colourID = glGetUniformLocation(shader.GetID(), "colour");
    glUniform3f(colourID, .7, .2f, .45f);


    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glVertexAttribPointer(vertexPosIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(vertexPosIndex);
	
    glDrawElements(GL_TRIANGLE_FAN, vertices.size(), GL_UNSIGNED_INT, NULL);
	
    glDisableVertexAttribArray(vertexPosIndex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(0);
	
    glUseProgram(NULL);
}

void Mesh::UpdateVertices()
{
	shader.SetVec3Attrib("vertexPos", transform.position);

	vertexPosIndex = shader.GetAttribute("vertexPos");
}