/**************************************************************************************************************
* Game - Code
*
* Instantiates SDL and OpenGL. Also instantiates all the game objects (The player, Targets, any level meshes).
* This is where the Render function is. The looped functions (render, update, fixed update) are all called from the main function.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/



#include "Game.h"
#include <vector>

#include "Terrain.h"

void Game::InitSDL()
{
	// Make the SDL stuff
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		print("could not initialize SDL2!")
		print(SDL_GetError())
		return;
	}

	// Set the window size = to the size of the user's monitor
	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);

	window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, display.w, display.h, SDL_WINDOW_OPENGL);

	if (!window)
	{
		print("could not initialise window!")
		print(SDL_GetError())
	}

	// Hide the mouse cursor
	SDL_ShowCursor(SDL_DISABLE);
}

void Game::InitOpenGL()
{
	// Make the OpenGL stuff
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if (!window)
	{
		print("Need to Initialise SDL before Initialising OpenGL.")
		return;
	}

	openGL_context = SDL_GL_CreateContext(window);
	if (!openGL_context)
	{
		print("Couldn't make OpenGL context.")
		print(SDL_GetError())
		return;
	}

	const GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) 
	{
		print("couldn't init")
		exit(EXIT_FAILURE);
	}
	
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		print("Unable to use V-sync")
		print(SDL_GetError())
	}
	rRunning = true;
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Game::InitObjects()
{
	skybox = new Skybox("Images/skydome.jpg");

	
	// tri = new TriangleRenderer(cam);

	//________ A cube ________\\

	const std::vector<std::string>& floorTex = {"Images/gravelBaseColour.jpg", "Images/gravelNormal.jpg"};
	terrain = new Terrain("Images/terrain-heightmap.png");
	
	player = new Player(rRunning);

	const auto left = new Model("ModelAssets/Cube.obj");
	const auto right = new Model("ModelAssets/Cube.obj");
	const auto back = new Model("ModelAssets/Cube.obj");
	const auto floor = new Model("ModelAssets/Cube.obj", floorTex);


	const auto box1 = new Model("ModelAssets/Cube.obj", floorTex);
	box1->AddPosition(0, 10, 0);
	
	left->SetScale(.2f, 7.5f, 7.5f);
	left->AddPosition(-7.5f, 5,0);

	right->SetScale(.2f, 7.5f, 7.5);
	right->AddPosition(7.5f, 5,0);
	
	back->SetScale(7.5f, 7.5f, .2f);
	back->AddPosition(0, 5, 7.5f);

	floor->AddPosition(0, 20, 0);
	floor->SetScale(100, 8, 400);
	floor->SetUvScale(100,400);
	floor->GetMesh()->SetMaterialSpecular(0);
	
	terrain->AddPosition(100, 5, -20);
	terrain->GetMesh()->SetMaterialSpecular(.1f);

	meshes =
	{
		terrain->GetMesh(), box1->GetMesh(), left->GetMesh(), right->GetMesh(), back->GetMesh(), floor->GetMesh()
	};
	player->SetLevelMeshes(meshes);

	// Determines how many targets should spawn in.
	constexpr unsigned short targetCount = 10;
	for(int i = 0; i < targetCount; i++)
	{
		// The chances that the target moves - 50%
		constexpr unsigned short movingOdds = 2;
		const unsigned short rnd = rand() % (movingOdds);
		Target* target = new Target(rnd == 0, player->GetPosition());
		targets.push_back(target);
	}
	
	// Ensures that at least one of the targets is moving
	bool hasMoving = false;
	for(const auto& target : targets)
	{
		target->SetMeshes(meshes);
		if(target->IsMoveable())
		{
			hasMoving = true; 
			break;
		}
	}
	if(!hasMoving) targets[0]->SetMoveable(true);

	player->SetTargets(targets);
}

void Game::Update(float deltaTime) const
{
	player->Update(deltaTime);
	for(const auto& target: targets) if(target) target->Update(deltaTime);
}

void Game::FixedUpdate(float deltaTime) const
{
	player->FixedUpdate(deltaTime);
	for(const auto& target: targets) if(target) target->FixedUpdate(deltaTime);
}

void Game::Render() const
{
	glClearColor(.04f, .01f, .1f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Drawing the player first so that the text in the UI has a background (hard to see otherwise)
	player->Render(light);
	
	for (const auto& mesh : player->GetLevelMeshes())
	{
		if(mesh) mesh->Render(player->GetCamera(), light);
	}
	
	if(skybox) skybox->Render(player->GetCamera(), light);

	for(const auto& target: targets) if(target) target->Render(player->GetCamera(), light);
	
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	SDL_GL_SwapWindow(window);
}

void Game::Clean()
{
	delete player;
	delete skybox;
	delete tri;
	
	// Terrain is the first mesh of the meshes vector... The mesh will try to be deleted twice
	delete terrain;
	meshes.erase(meshes.begin());
	
	for (const auto& mesh : meshes) delete mesh;
	for (const auto& target : targets) delete target;
	meshes.clear();
	targets.clear();


		
	SDL_DestroyWindow(window);
	SDL_Quit();
}
