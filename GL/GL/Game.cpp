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

	std::string floorTex[] = {"Images/gravelBaseColour.jpg", "Images/gravelNormal.jpg"};
	terrain = new Terrain("Images/terrain-heightmap.png");
	
	player = new Player(rRunning);
	
	auto left = new Model("ModelAssets/Cube.obj");
	auto right = new Model("ModelAssets/Cube.obj");
	auto back = new Model("ModelAssets/Cube.obj");
	auto floor = new Model("ModelAssets/Cube.obj");

	
	auto box1 = new Model("ModelAssets/Cube.obj", floorTex);

	left->SetScale(.2f, 7.5f, 7.5f);
	left->AddPosition(-7.5f, 5,0);

	right->SetScale(.2f, 7.5f, 7.5);
	right->AddPosition(7.5f, 5,0);
	
	back->SetScale(7.5f, 7.5f, .2f);
	back->AddPosition(0, 5, 7.5f);

	floor->AddPosition(0, 20, 0);
	floor->SetScale(100, 8, 400);
	floor->SetUvScale(200,200);
	
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
		// The chances that the target moves - 25%
		constexpr unsigned short movingOdds = 3;
		const unsigned short rnd = rand() % (movingOdds);
		Target* target = new Target(rnd == 0, player->GetPosition());
		targets.push_back(target);
	}
	
	// Ensures that atleast one of the targets is moving
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
	glClearColor(.04f, .01f, .1f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	player->Render(light);
	
	for (const auto& mesh : player->GetLevelMeshes())
	{
		// if(mesh) mesh->Render(player->GetCamera(), light);
	}

	// if(skybox) skybox->Render(player->GetCamera(), light);

	// for(const auto& target: targets) if(target) target->Render(player->GetCamera(), light);
	
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	SDL_GL_SwapWindow(window);
}
