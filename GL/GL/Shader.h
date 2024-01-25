#pragma once

#include <iostream>
#include <glew.h>
#define print(x) { std::cout << x << std::endl; }

class Shader
{
public:
    Shader() { }
    Shader(const GLchar* properties[]);
    ~Shader() { glDeleteProgram(program_id); }
    
    void MakeShader();

    // Gets
    GLuint GetID() const { return program_id; }
    GLint GetAttribute(const GLchar* attribName) const { return glGetAttribLocation(program_id, attribName); }

private:
    GLuint program_id;
};