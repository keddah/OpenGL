#include "Mesh.h"

#include "Shader.h"

Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
{
    // glGenVertexArrays(1, &vertex_array);
    // glGenBuffers(1, &vertex_buffer);
    // glGenBuffers(1, &element_buffer);
    //
    // glBindVertexArray(vertex_array);
    //
    // // Buffers
    // glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    //
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    //
    // // Set vertex attribute pointers
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    //
    // // Unbind VAO
    // glBindVertexArray(0);
    //
    // Shader shader = Shader();
    // shader.MakeShader();

    InitShaders();
    InitVertices();
}

void Mesh::Render() const
{
    // Bind VAO
    glBindVertexArray(vertex_array);

    // Draw the mesh using indices
    glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);

    // Unbind VAO
    glBindVertexArray(0);
}

void Mesh::InitVertices()
{
    // The vertex buffer (positions of all the vertices)
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(GLfloat), &vertices, GL_STATIC_DRAW);

    constexpr GLint indices[] = { 0, 1, 2 };

    // The index buffer (the correlation between the vertices)
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLint), indices, GL_STATIC_DRAW);
}

void Mesh::InitShaders()
{
    shader.MakeShader();

    vertexPosIndex = shader.GetAttribute("vertexPos");

    if (vertexPosIndex == -1)
    {
        print("couldn't get the attribute")
        print(glGetError())
        return false;
    }

    model_matrix_address = glGetUniformLocation(shader.GetID(), "modelMatrix");
    view_matrix_address = glGetUniformLocation(shader.GetID(), "viewMatrix");
    projection_matrix_address = glGetUniformLocation(shader.GetID(), "projectionMatrix");
	
    return true;
}
