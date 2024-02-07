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
            char* log = new char[logLength];
            glGetShaderInfoLog(shader, logLength, NULL, log);
            log[logLength] = 0;
            printf(log);
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