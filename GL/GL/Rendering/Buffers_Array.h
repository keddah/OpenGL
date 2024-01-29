#pragma once
#include <glew.h>
#include <vector>

class VertexBuffer
{
public:
    VertexBuffer() = default;
    VertexBuffer(const std::vector<GLfloat>& vertices);
	~VertexBuffer() { Delete(); }
	
    void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, id); }
    void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
    void Delete() const { glDeleteBuffers(1, & id); }

	GLuint GetID() const { return id;}

	
private:
    GLuint id; 
};


class IndexBuffer
{
public:
    IndexBuffer() = default;
    IndexBuffer(const std::vector<GLuint>& indices);
	~IndexBuffer() { Delete(); }

	void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
	void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
	void Delete() const { glDeleteBuffers(1, & id); }

	GLuint GetID() const { return id;}
	
private:
    GLuint id; 
};


class VertexArray
{
public:
    VertexArray();
	~VertexArray() { Delete(); }

    // Links a VBO to the VAO using a certain layout
    void LinkBuffer(GLuint vertAttribAddress);
    void Bind() const { glBindVertexArray(id); }
    void Unbind() const { glBindVertexArray(0); }
    void Delete() const { glDeleteVertexArrays(1, &id); }

	GLuint GetID() const { return id;}

private:
    GLuint id; 
};