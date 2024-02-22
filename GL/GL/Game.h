/**************************************************************************************************************
* Game - Header
*
* Defines pointers for the player, terrain and skybox as well as creates vectors for the targets and level meshes.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/



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
	void Clean();

private:
	// Need to initialise SDL before OpenGL
	void Init() { InitSDL(); InitOpenGL(); InitObjects(); }
	void InitSDL();
	void InitOpenGL();
	void InitObjects();

	// This is a reference so that the game can be ended easier by the player
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
