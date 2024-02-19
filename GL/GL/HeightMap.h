#pragma once

#include <stb_image.h>
#include <iostream>
#include <string>

#define print(x) { std::cout << x << std::endl; }
#define GetError() { GLenum error = glGetError(); if (error != GL_NO_ERROR) { print("Error: " << gluErrorString(error)); } }
#define glCall(theFunction) { theFunction; GetError(); }

using namespace std;

class HeightMap
{
public:
    HeightMap(string filePath);
};
