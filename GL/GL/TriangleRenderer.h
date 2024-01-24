#pragma once
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <glm.hpp>
#include<iostream>

#include "Shader.h"

#define print(x) { std::cout << x << std::endl; }


class TriangleRenderer
{
public:
	TriangleRenderer() { Init(); };
	~TriangleRenderer() { Clean(); }

	void Update();
	void Render();
	void Clean() { glDeleteProgram(shader.GetID()); }

private:
	void Init() { if(InitShaders()) InitVertices(); }
	bool InitShaders();
	void InitVertices();

	GLfloat vertices[6] =
	{
		-.5f, .5f, // top left
		-.5f, 0, // bottom left
		.5f, .5f, // right
	};

	GLint vertex_position = -1;

	GLuint vertex_buffer;
	GLuint index_buffer;

	Shader shader;
};

