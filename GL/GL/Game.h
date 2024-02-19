#pragma once

#include <iostream>

#include "TriangleRenderer.h"
#include "Mesh.h"
#include "Model.h"
#include "Player.h"
#include "Skybox.h"

#define print(x) { std::cout << x << std::endl; }

class Game
{
public:
	Game(bool& running) : rRunning(running) { Init(); }
	~Game() { Clean(); }

	void Update(float deltaTime) const;
	void FixedUpdate(float deltaTime) const;

	void Render() const;
	void Clean() const;

	struct Vertex
	{
		glm::vec3 position;
		glm::vec4 colour;
	};
	
private:
	// Need to initialise SDL before OpenGL
	void Init() { InitSDL(); InitOpenGL(); InitObjects(); }
	void InitSDL();
	void InitOpenGL();
	void InitObjects();

	bool& rRunning;
	
	SDL_Window* window;
	SDL_GLContext openGL_context;

	std::vector<Mesh*> meshes;
	
	TriangleRenderer* tri;

	std::vector<Target*> targets;
	
	Skybox* skybox;
	
	Terrain* terrain;
	Player* player;
	Light light;
};
