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
	void FixedUpdate(float deltaTime);

	void Render() const;
	void Clean() const { delete tri; for (const auto& mesh : meshes) delete mesh; SDL_DestroyWindow(window); SDL_Quit(); }

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

	std::vector<Mesh*> meshes;
	
	TriangleRenderer* tri;
	
	Model* model;
	Skybox* skybox;
	
	Player* player;
	Light light;
};
