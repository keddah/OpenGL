/**************************************************************************************************************
* Utilities - Header
*
* Responsible for reading shader files and supplying debugging functions. 
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#pragma once

#include <string>
#include <fstream>
#include <glew.h>

#include <iostream>
#define print(x) { std::cout << x << std::endl; }

using namespace std;

namespace Util
{
    string ReadFile(string file)
    {
        string file_str;
        ifstream fstream(file.c_str());
        file_str.assign((std::istreambuf_iterator<char>(fstream)), std::istreambuf_iterator<char>());
        return file_str;
    }

    void PrintShaderLog(const GLuint shader)
    {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        
        if (logLength > 0)
        {
            const auto log = new GLchar[logLength];
            glGetShaderInfoLog(shader, logLength, NULL, log);
            print("Shader Log:\n" << log);
            delete[] log;
        }
    }

    void PrintProgramLog(const GLuint program)
    {
        GLsizei len;
        char error[1500];

        glGetProgramInfoLog(program, 1500, &len, error);
        print("Program Linking Log:\n\n" << error);

        glDeleteProgram(program);  // Delete the program to avoid using a partially linked program
    }
};