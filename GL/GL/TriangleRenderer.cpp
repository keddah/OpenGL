#include "TriangleRenderer.h"

GLint indices[] = { 0, 1, 2 };


bool TriangleRenderer::InitShaders()
{
	shader.MakeShader();

	vertex_position = shader.GetAttributes("vertexPos2D");

	if (vertex_position == -1)
	{
		print("couldn't get the attribute")


			print(glGetError())
			return false;
	}

	return true;
}

void TriangleRenderer::InitVertices()
{
	// The vertex buffer (positions of all the vertices)
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	// The index buffer (the correlation between the vertices)
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLint), indices, GL_STATIC_DRAW);

}

void TriangleRenderer::Render()
{
	glUseProgram(shader.GetID());

	GLint colorID = glGetUniformLocation(shader.GetID(), "color");
	glUniform3f(colorID, 0.2f, 0.3f, 0.0);

		glEnableVertexAttribArray(vertex_position);

			glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
			glVertexAttribPointer(vertex_position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
				glDrawElements(GL_TRIANGLE_FAN, 3, GL_UNSIGNED_INT, NULL);
	
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
			glBindBuffer(GL_ARRAY_BUFFER, NULL);
		glDisableVertexAttribArray(vertex_position);
	glUseProgram(NULL);
}