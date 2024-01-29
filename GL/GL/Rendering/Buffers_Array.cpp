#include "Buffers_Array.h"

VertexBuffer::VertexBuffer(const std::vector<GLfloat>& vertices)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

}

IndexBuffer::IndexBuffer(const std::vector<GLuint>& indices)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
}

void VertexArray::LinkBuffer(const GLuint vertAttribAddress)
{
    Bind();  // Bind the VAO
    glVertexAttribPointer(vertAttribAddress, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertAttribAddress);
}
