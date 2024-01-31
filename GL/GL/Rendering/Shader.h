#pragma once

#include <iostream>
#include <glew.h>
#include <glm.hpp>

#define print(x) { std::cout << x << std::endl; }
#define GetError() { GLenum error = glGetError(); if (error != GL_NO_ERROR) { print("Error during texture setup: " << gluErrorString(error)); } }
#define glCall(theFunction) { theFunction; GetError(); }

class Shader
{
public:
    Shader() { }
    Shader(const GLchar* properties[]);
    ~Shader() { glDeleteProgram(program_id); }
    
    void Init();

    void Activate() const { glCall(glUseProgram(program_id)); }
    void Deactivate() const { glCall(glUseProgram(0)); }
    
    void SetFloatAttrib(const GLchar* attribName, float newValue) const;
    
    void SetVec3Attrib(const GLchar* attribName, glm::vec3 newValue) const;
    void SetVec3Attrib(const GLchar* attribName, float x, float y, float z) const;
    
    void SetVec4Attrib(const GLchar* attribName, glm::vec4 newValue) const;
    void SetVec4Attrib(const GLchar* attribName, float x, float y, float z, float w) const;
    
    void SetMat4Attrib(const GLchar* attribName, glm::mat4 newValue) const;
    
    void SetUintAttrib(const GLchar* attribName, unsigned int newValue) const;
    void SetIntAttrib(const GLchar* attribName, int newValue) const;

    // Gets
    GLuint GetID() const { return program_id; }
    GLint GetAttribute(const GLchar* attribName) const { return glGetAttribLocation(program_id, attribName); }
    

private:
    GLuint program_id;
};