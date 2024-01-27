#pragma once

#include <iostream>
#include <glew.h>
#include <glm.hpp>

#define print(x) { std::cout << x << std::endl; }

class Shader
{
public:
    Shader() { }
    Shader(const GLchar* properties[]);
    ~Shader() { glDeleteProgram(program_id); }
    
    void Init();

    
    void SetFloatAttrib(const GLchar* attribName, float newValue) const;
    
    void SetVec3Attrib(const GLchar* attribName, glm::vec3 newValue) const;
    void SetVec3Attrib(const GLchar* attribName, float x, float y, float z) const;
    
    void SetVec4Attrib(const GLchar* attribName, glm::vec4 newValue) const;
    void SetVec4Attrib(const GLchar* attribName, float x, float y, float z, float w) const;
    
    void SetUintAttrib(const GLchar* attribName, unsigned int newValue) const;
    void SetIntAttrib(const GLchar* attribName, int newValue) const;

    // Gets
    GLuint GetID() const { return program_id; }
    GLint GetAttribute(const GLchar* attribName) const { return glGetAttribLocation(program_id, attribName); }
    

private:
    GLuint program_id;
};