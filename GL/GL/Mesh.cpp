#include "Mesh.h"



Mesh::Mesh(GLfloat _vertices[], GLuint _indices[], Camera& camera) : rCam(camera)
{
	vertices = _vertices;
	indices = _indices;

    // If shader initialisation was successful, init the vertices.
    if(InitShaders()) InitVertices();
}

void Mesh::InitVertices()
{
	vArray.Bind();
	
	// The vertex buffer (positions of all the vertices)
	vBuffer = new VertexBuffer(vertices, sizeof(vertices));

	// The index buffer (the correlation between the vertices)
	iBuffer = new IndexBuffer(indices, sizeof(indices));
	
	// Links VBO to VAO
	vArray.LinkBuffers(*vBuffer, vertexPosIndex);
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

void Mesh::Render()
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
	
	shader.SetVec4Attrib("colour", .7, .2f, .45f, 1);

	glEnableVertexAttribArray(vertexPosIndex);
	
	vBuffer->Bind();
	iBuffer->Bind();
	vArray.LinkBuffers(*vBuffer, vertexPosIndex);
	
	glDrawElements(GL_TRIANGLE_FAN, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, nullptr);
	
	glDisableVertexAttribArray(vertexPosIndex);
	iBuffer->Unbind();  // Unbind index buffer after drawing
	vBuffer->Unbind();  // Unbind vertex buffer after drawing
	vArray.Unbind();    // Unbind vertex array object last


	glUseProgram(NULL);
}

void Mesh::UpdateVertices()
{
	shader.SetVec3Attrib("vertexPos", transform.position);

	vertexPosIndex = shader.GetAttribute("vertexPos");
}