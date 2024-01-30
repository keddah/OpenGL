#pragma once
#include <glew.h>
#include <vector>

class BufferArrayManager
{
public:
    BufferArrayManager(const std::vector<GLfloat>& verts, const std::vector<GLuint>& indices);
    ~BufferArrayManager() { DeleteAll(); }

    void SetArrayAttrib(GLuint index, GLuint componentCount, GLenum type, GLsizei stride, const void* offset) const;
    
    void BindAll() const { BindVBuffer(); BindIBuffer(); BindArray(); }
    void BindVBuffer() const { glBindBuffer(GL_ARRAY_BUFFER, vBuffer); }
    void BindIBuffer() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer); }
    void BindArray() const { glBindVertexArray(vArray); }

    void UnbindAll() const { UnbindVArray(); UnbindIBuffer(); UnbindVArray(); }
    void UnbindVBuffer() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
    void UnbindIBuffer() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
    void UnbindVArray() const { glBindVertexArray(0); }
    void DeleteAll() const { glDeleteBuffers(1, &vBuffer); glDeleteBuffers(1, &iBuffer); glDeleteVertexArrays(1, &vArray); }

    GLuint VBufferID() const { return vBuffer; }
    GLuint IBufferID() const { return iBuffer; }
    GLuint VArrayID() const { return vArray; }
    
private:
    GLuint vBuffer, iBuffer, vArray;
};
