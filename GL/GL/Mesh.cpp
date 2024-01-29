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
	v_buffer = VertexBuffer(vertices);
	i_buffer = IndexBuffer(indices);
	v_array = new VertexArray();
	
	v_buffer.Unbind();
	i_buffer.Unbind();
	v_array->Unbind();
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
	
    // glUnifrom used to set values on the GPU
	shader.SetVec4Attrib("colour", 0, .2f, .45f, 1);


	v_buffer.Bind();
	i_buffer.Bind();
	v_array->LinkBuffer(vertexPosIndex);
	
	GLsizei len;
	GLchar error[100];

	glGetProgramInfoLog(v_array->GetID(), 1500, &len, error);
	print("Program Linking Log:\n\n" << error);
	
    glDrawElements(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_INT, &indices);


	// glDeleteProgram(v_buffer.GetID());  // Delete the program to avoid using a partially linked program
	
    glDisableVertexAttribArray(vertexPosIndex);
	v_buffer.Unbind();
	i_buffer.Unbind();
	v_array->Unbind();
	
    glUseProgram(NULL);
}