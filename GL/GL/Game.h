#pragma once

#include <iostream>

#include "Controller.h"

#include "TriangleRenderer.h"

#define print(x) { std::cout << x << std::endl; }

class Game
{
public:
	Game(bool& running) : rRunning(running) { Init(); }
	~Game() { Clean(); }

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);

	void Render() const;
	void Clean() const { delete tri; SDL_DestroyWindow(window); SDL_Quit(); }

private:
	// Need to initialise SDL before OpenGL
	void Init() { InitSDL(); InitOpenGL(); }
	void InitSDL();
	void InitOpenGL();

	bool& rRunning;
	
	SDL_Window* window;
	SDL_GLContext openGL_context;

	TriangleRenderer* tri;

	Controller controller { rRunning };
	Camera cam { controller };
};