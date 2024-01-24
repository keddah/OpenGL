#pragma once

#include <iostream>
#include "SDL.h"
#include "glew.h"

#include "Shader.h"
#include "TriangleRenderer.h"

#define print(x) { std::cout << x << std::endl; }

class Game
{
public:
	Game();
	~Game() { Clean(); }

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);

	void Render();
	void Clean() const;

private:
	// Need to initialise SDL before OpenGL
	void Init() { InitSDL(); InitOpenGL(); }
	void InitSDL();
	void InitOpenGL();

	SDL_Window* window;
	SDL_GLContext openGL_context;

	TriangleRenderer* tri;
};

