#include "Buffer_Array.h"

void VertexBuffer::Init(GLfloat vertices[], GLsizeiptr size)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}


void IndexBuffer::Init(GLuint indices[], const GLsizeiptr size)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}


void VArrayBuffer::LinkBuffers(const VertexBuffer& vbo, GLuint vertAttribAddress) const
{
    Bind();
    vbo.Bind();
    glVertexAttribPointer(vertAttribAddress, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(nullptr));
    glEnableVertexAttribArray(vertAttribAddress);
    vbo.Unbind();
    Unbind();

    GLsizei len;
    char error[1500];

    glGetProgramInfoLog(vertAttribAddress, 1500, &len, error);
    print("Program Linking Log:\n\n" << std::string(error));
}
