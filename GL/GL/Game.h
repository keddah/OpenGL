#pragma once

#include <iostream>

#include "Controller.h"
#include "TriangleRenderer.h"
#include "Mesh.h"

#define print(x) { std::cout << x << std::endl; }

class Game
{
public:
	Game(bool& running) : rRunning(running) { Init(); }
	~Game() { Clean(); }

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);

	void Render() const;
	void Clean() const { delete tri; delete mesh; SDL_DestroyWindow(window); SDL_Quit(); }

	struct Vertex
	{
		glm::vec3 position;
		glm::vec4 colour;
	};
	
private:
	// Need to initialise SDL before OpenGL
	void Init() { InitSDL(); InitOpenGL(); }
	void InitSDL();
	void InitOpenGL();

	bool& rRunning;
	
	SDL_Window* window;
	SDL_GLContext openGL_context;

	TriangleRenderer* tri;
	Mesh* mesh;
	
	Controller controller { rRunning };
	Camera cam { controller };
};
