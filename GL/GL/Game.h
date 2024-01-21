#pragma once

#include <iostream>
#include "SDL.h"
#include "glew.h"

#define print(x) { std::cout << x << std::endl; }

class Game
{
public:
	Game();
	~Game() { Clean(); }

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);

	void Render();
	void Clean();

private:
	// Need to initialise SDL before OpenGL
	void Init() { InitSDL(); InitOpenGL(); }
	void InitSDL();
	void InitOpenGL();
	void triangle();

	SDL_Window* window;
	SDL_GLContext openGL_context;

	// Vertex Shader source code
	const char* vert_shader_source = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	//Fragment Shader source code
	const char* fragment_shader_source = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
		"}\n\0";


	GLuint shader_program;

	GLuint vert_array;
	GLuint vert_buffer;
};

