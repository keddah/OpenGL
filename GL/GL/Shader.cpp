#include "Shader.h"

Shader::Shader(GLuint program, const std::string& properties)
{
    _properties = properties;
    shader_program = program;
}

void Shader::CreateShader()
{
    const char* props = _properties.c_str();
    
    shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &props, nullptr);
    glCompileShader(shader);

    glAttachShader(shader_program, shader);
    glLinkProgram(shader_program);

    // Since everything has been assigned... it's not needed anymore
    Delete();
}
