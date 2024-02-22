/**************************************************************************************************************
* Vertex Buffer/Vertex Array Manager - Code
*
* This class manages the buffers and vertex array for meshes. This class was created so that managing the buffers/array was easier
* and all in one place.
* Responsible for generating the buffers and vertex array and setting vertex attributes. 
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#include "BufferArrayManager.h"

BufferArrayManager::BufferArrayManager(const std::vector<GLfloat>& vertData, const std::vector<GLuint>& indices)
{
    glCall(glGenVertexArrays(1, &vArray));
    glCall(glBindVertexArray(vArray));

    // The vertex buffer (positions of all the vertices)
    glCall(glGenBuffers(1, &vBuffer));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, vBuffer));
    glCall(glBufferData(GL_ARRAY_BUFFER, vertData.size() * sizeof(GLfloat), vertData.data(), GL_STATIC_DRAW));

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
