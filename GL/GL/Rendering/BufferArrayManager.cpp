#include "BufferArrayManager.h"

BufferArrayManager::BufferArrayManager(const std::vector<GLfloat>& verts, const std::vector<GLuint>& indices)
{
    glCall(glGenVertexArrays(1, &vArray));
    glCall(glBindVertexArray(vArray));

    // The vertex buffer (positions of all the vertices)
    glCall(glGenBuffers(1, &vBuffer));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, vBuffer));
    glCall(glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW));

    // The index buffer (the correlation between the vertices)
    glCall(glGenBuffers(1, &iBuffer));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW));

    // Unbind everything once everything has been created
    glCall(glBindVertexArray(0));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, NULL));
}

void BufferArrayManager::SetArrayAttrib(const GLuint index, GLuint componentCount, const GLenum type, GLsizei stride, const void* offset) const
{
    glCall(glVertexAttribPointer(index, componentCount, type, GL_FALSE, stride, offset));
    glCall(glEnableVertexAttribArray(index));
}
