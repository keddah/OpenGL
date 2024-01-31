#include "BufferArrayManager.h"

BufferArrayManager::BufferArrayManager(const std::vector<GLfloat>& verts, const std::vector<GLuint>& indices)
{
    // The vertex buffer (positions of all the vertices)
    glCall(glGenBuffers(1, &vBuffer));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, vBuffer));
    glCall(glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW));

    // The index buffer (the correlation between the vertices)
    glCall(glGenBuffers(1, &iBuffer));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW));

    glCall(glGenVertexArrays(1, &vArray));
    glCall(glBindVertexArray(vArray));

    // Sets up the vertices so that the GPU knows that its position is a vector 3.
    SetArrayAttrib(0, 3, GL_FLOAT, 9 * sizeof(GLfloat), nullptr);
    SetArrayAttrib(1, 4, GL_FLOAT, 9 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    SetArrayAttrib(2, 2, GL_FLOAT, 9 * sizeof(GLfloat), reinterpret_cast<void*>(7 * sizeof(GLfloat)));

    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, NULL));
    glCall(glBindVertexArray(0));
}

GLuint BufferArrayManager::SetArrayAttrib(const GLuint index, GLuint componentCount, const GLenum type, GLsizei stride, const void* offset) const
{
    BindVBuffer();
    glCall(glVertexAttribPointer(index, componentCount, type, GL_FALSE, stride, offset));
    glCall(glEnableVertexAttribArray(index));
    UnbindVBuffer();

    // Returns the component count so that the offset can be calculated automatically
    return componentCount;
}
