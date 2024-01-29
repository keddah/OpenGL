#pragma once
#include <glew.h>
#include <vector>
#include <iostream>

#define print(x) { std::cout << x << std::endl; }

//____________________ Vertex  Buffer ____________________\\

class VertexBuffer
{
public:
    VertexBuffer(GLfloat vertices[], GLsizeiptr size) { Init(vertices, size); }
    ~VertexBuffer() { Delete(); }
    
    void Init(GLfloat vertices[], GLsizeiptr size);
    void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, id); }
    void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
    void Delete() const { glDeleteBuffers(1, &id); }

    GLuint GetID() const { return id; }

private:
    GLuint id;
};



//____________________ Index Buffer ____________________\\

class IndexBuffer
{
public:
    IndexBuffer(GLuint indices[], GLsizeiptr size) { Init(indices, size); }
    ~IndexBuffer() { Delete(); }
    void Init(GLuint indices[], GLsizeiptr size);

    void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
    void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
    void Delete() const { glDeleteBuffers(1, &id); }

    GLuint GetID() const { return id; }

private:
    GLuint id;
};



//____________________ Vertex Array Buffer ____________________\\

class VArrayBuffer
{
public:
    VArrayBuffer() { glGenVertexArrays(1, &id); }
    ~VArrayBuffer() { Delete(); }
    
    void LinkBuffers(const VertexBuffer& vbo, GLuint vertAttribAddress) const;
    void Bind() const { glBindVertexArray(id); }
    void Unbind() const {  glBindVertexArray(0); }
    void Delete() const { glDeleteVertexArrays(1, &id); }

    GLuint GetID() const { return id; }
    
private:
    GLuint id;
    
};
