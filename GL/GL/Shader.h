#pragma once

#include <iostream>
#include "glew.h"
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
    GLint GetAttributes(const GLchar* attribName) const { return glGetAttribLocation(program_id, attribName); }

private:
    GLuint program_id;
};


#include <string>
#include <fstream>
using namespace std;

namespace FileReader
{
    string ReadFile(string file)
    {
        string file_str;
        ifstream fstream(file.c_str());
        file_str.assign((std::istreambuf_iterator<char>(fstream)), std::istreambuf_iterator<char>());
        return file_str;
    };

    void PrintShaderLog(GLuint shader)
    {
        int infoLength;
        int maxLength;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength];
        glGetShaderInfoLog(shader, maxLength, &infoLength, infoLog);

        if (infoLength > 0)
        {
            printf("%s\n", infoLog);
        }

        delete[] infoLog;
    };
};