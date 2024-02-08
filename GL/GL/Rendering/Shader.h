#pragma once

#include <iostream>
#include <glew.h>
#include <glm.hpp>
#include <string>

#define print(x) { std::cout << x << std::endl; }
#define GetError() { GLenum error = glGetError(); if (error != GL_NO_ERROR) { print("Error: " << gluErrorString(error)); } }
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
    
    void SetFloatAttrib(const std::string& attribName, float newValue) const;
    float GetFloatAttrib(const std::string& attribName) const;
    
    void SetVec3Attrib(const std::string& attribName, glm::vec3 newValue) const;
    void SetVec3Attrib(const std::string& attribName, float x, float y, float z) const;
    
    void SetVec4Attrib(const std::string& attribName, glm::vec4 newValue) const;
    void SetVec4Attrib(const std::string& attribName, float x, float y, float z, float w) const;
    
    void SetMat4Attrib(const std::string& attribName, glm::mat4 newValue) const;
    
    void SetUintAttrib(const std::string& attribName, unsigned int newValue) const;
    unsigned int GetUintAttrib(const std::string& attribName) const;
    
    void SetIntAttrib(const std::string& attribName, int newValue) const;
    int GetIntAttrib(const std::string& attribName) const;

    
    // Gets
    GLuint GetID() const { return program_id; }
    GLint GetAttribute(const std::string& attribName) const { return glGetAttribLocation(program_id, attribName.c_str()); }
    

private:
    GLuint program_id;
};