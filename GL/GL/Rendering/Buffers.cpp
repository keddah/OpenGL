#include "Buffers.h"

VertexBuffer::VertexBuffer(const void* data, GLuint size)
{
    // The vertex buffer (positions of all the vertices)
    glGenBuffers(1, &rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(GLuint* data, GLuint count)
{
    index_count = count;
    
    // The vertex buffer (positions of all the vertices)
    glGenBuffers(1, &rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}
