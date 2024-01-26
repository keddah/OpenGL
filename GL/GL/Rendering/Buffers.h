#pragma once
#include <glew.h>

class VertexBuffer
{
public:
    VertexBuffer(const void* data, GLuint size);
    ~VertexBuffer() { glDeleteBuffers(1,&rendererId); }

    void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, rendererId); }
    void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
    void Delete() const { glDeleteBuffers(1, &rendererId); }

private:
    GLuint rendererId;    
};


class IndexBuffer
{
public:
    IndexBuffer(GLuint* data, GLuint count);
    ~IndexBuffer() { glDeleteBuffers(1,&rendererId); }

    void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, rendererId); }
    void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
    void Delete() const { glDeleteBuffers(1, &rendererId); }
    
    GLuint GetCount() const { return index_count; }
    
private:
    GLuint rendererId, index_count;
};
