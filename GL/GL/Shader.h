#pragma once

#include <iostream>
#include "glew.h"

class Shader
{
public:
    Shader(GLuint program, const std::string& properties);
    void Delete() { glDeleteShader(shader); }
    
    // Replaces the current properties
    void SetProperties(const std::string& properties) { _properties = properties; }

    // Adds on to the existing properties
    void AddProperties(const std::string& properties) { _properties += "\n" + properties; }

    GLuint GetShader() const { return shader; }

private:
    std::string _properties;
    GLuint shader;
};
