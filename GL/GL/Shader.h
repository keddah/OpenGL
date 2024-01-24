#pragma once

#include <iostream>
#include "glew.h"

class Shader
{
public:
    Shader(GLuint program, const std::string& properties);
    void Delete() const { glDeleteShader(shader); }
    
    // Replaces the current properties then recreates the shader
    void SetProperties(const std::string& properties) { _properties = properties; CreateShader(); }

    // Adds on to the existing properties then recreates the shader
    void AddProperties(const std::string& properties) { _properties += "\n" + properties; CreateShader(); }

private:
    void CreateShader();

    GLuint shader_program;
    std::string _properties;
    GLuint shader;

    void Colouring();
};
