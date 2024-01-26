#include "Mesh.h"

#include <random>
#include <gtc/type_ptr.hpp>

#include "Rendering/Shader.h"

Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, Camera& camera) : rCam(camera)
{
    index_count = indices.size();
    // If shader initialisation was successful, init the vertices.
    if(InitShaders()) InitVertices(vertices, indices);
}

void Mesh::Render() const
{
    glUseProgram(shader.GetID());

    constexpr glm::vec3 translation = {};
    constexpr glm::vec3 rotation = {90, 0, 0};
    constexpr glm::vec3 scale = {1, 1, 1};

	
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = rotate(modelMatrix, static_cast<float>(rotation.x * 180 / std::_Pi), {1,0,0});
    modelMatrix = rotate(modelMatrix, static_cast<float>(rotation.y * 180 / std::_Pi), {0,1,0});
    modelMatrix = rotate(modelMatrix, static_cast<float>(rotation.z * 180 / std::_Pi), {0,0,1});
	
    modelMatrix = translate(modelMatrix, translation);
	
    modelMatrix = glm::scale(modelMatrix, scale);

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
	
    glDrawElements(GL_TRIANGLE_FAN, 3, GL_UNSIGNED_INT, NULL);
	
    glDisableVertexAttribArray(vertexPosIndex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
	
    glUseProgram(NULL);
}

void Mesh::InitVertices(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
{
    // The vertex buffer (positions of all the vertices)
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(GLfloat), &vertices, GL_STATIC_DRAW);

    // The index buffer (the correlation between the vertices)
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLint), &indices, GL_STATIC_DRAW);
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
