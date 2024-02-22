/**************************************************************************************************************
* Vertex Buffer/Vertex Array Manager - Header
*
* This class manages the buffers and vertex array for meshes. This class was created so that managing the buffers/array was easier
* and all in one place.
* Creates functions that manage the buffers...
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#pragma once

#include <glew.h>
#include <vector>
#include <glm.hpp>
#include <iostream>


#define print(x) { std::cout << x << std::endl; }
#define GetError() { GLenum error = glGetError(); if (error != GL_NO_ERROR) { print("error code: " << error << "\n" << gluErrorString(error)); __debugbreak(); } }
#define glCall(theFunction) { theFunction; GetError(); }

struct Vertex
{
    GLfloat position[3];
    GLfloat normals[3];
    GLfloat texCoords[2];

    static GLuint PositionCount() { return 3; }
    static GLuint NormalCount() { return sizeof(normals) / sizeof(normals[0]); }
    static GLuint TexCoordsCount() { return sizeof(texCoords) / sizeof(texCoords[0]); }
    static GLuint GetCount() { return PositionCount() + NormalCount() + TexCoordsCount(); }

    glm::vec3 GetPositionVec() const { return {position[0], position[1], position[2]}; }
    glm::vec3 GetNormalVec() const { return {normals[0], normals[1], normals[2]}; }
    glm::vec2 GetUvVec() const { return {texCoords[0], texCoords[1]}; }
};

class BufferArrayManager
{
public:
    BufferArrayManager(const std::vector<GLfloat>& vertData, const std::vector<GLuint>& indices);
    ~BufferArrayManager() { DeleteAll(); }

    void SetArrayAttrib(GLuint index, GLuint componentCount, GLenum type, GLsizei stride, const void* offset) const;
    
    void BindAll() const { BindVBuffer(); BindIBuffer(); BindArray(); }
    void BindVBuffer() const { glCall(glBindBuffer(GL_ARRAY_BUFFER, vBuffer)); }
    void BindIBuffer() const { glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer)); }
    void BindArray() const { glCall(glBindVertexArray(vArray)); }

    void UnbindAll() const { UnbindVArray(); UnbindIBuffer(); UnbindVArray(); }
    void UnbindVBuffer() const { glCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
    void UnbindIBuffer() const { glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); }
    void UnbindVArray() const { glCall(glBindVertexArray(0)); }
    void DeleteAll() const
    {
        if(vBuffer) glCall(glDeleteBuffers(1, &vBuffer));
        if(iBuffer) glCall(glDeleteBuffers(1, &iBuffer));
        if(vArray) glCall(glDeleteVertexArrays(1, &vArray));
    }

    GLuint VBufferID() const { return vBuffer; }
    GLuint IBufferID() const { return iBuffer; }
    GLuint VArrayID() const { return vArray; }
    
private:
    GLuint vBuffer, iBuffer, vArray;
};
