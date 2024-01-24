#pragma once

#include <iostream>
#include "glew.h"
#define print(x) { std::cout << x << std::endl; }

class Shader
{
public:
    Shader() { }
    Shader(const GLchar* properties[]);
    ~Shader() { /*glDeleteProgram(program_id);*/ }
    

    // Gets
    GLuint GetID() const { return program_id; }
    GLint GetAttributes(const GLchar* attribName) const { return glGetAttribLocation(program_id, attribName); }

    void MakeShader();
private:
    GLuint program_id;

};

