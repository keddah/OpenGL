#include "Shader.h"

Shader::Shader(GLuint program, const std::string& properties)
{
    _properties = properties;
    const char* props = _properties.c_str();
    
    shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &props, nullptr);
    glCompileShader(shader);

    glAttachShader(program, shader);
    glLinkProgram(program);
}