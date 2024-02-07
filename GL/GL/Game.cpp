#include "Game.h"
#include <vector>

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
	// tri = new TriangleRenderer(cam);

	//________ A cube ________\\

	const std::vector<GLfloat> vertData =
	{
		// Front Face
		 -0.5f, -0.5f, 0.5f,   /* Vertex 0 */    /* TexCoord */  0,0,
		 0.5f, -0.5f,  0.5f,   /* Vertex 1 */    /* TexCoord */  1,0,
		 0.5f,  0.5f,  0.5f,   /* Vertex 2 */    /* TexCoord */  1,1,
		-0.5f,  0.5f,  0.5f,   /* Vertex 3 */    /* TexCoord */  0,1,

		// Back Face
		-0.5f, -0.5f, -0.5f,   /* Vertex 4 */    /* TexCoord */  0,0,
		 0.5f, -0.5f, -0.5f,   /* Vertex 5 */    /* TexCoord */  1,0,
		 0.5f,  0.5f, -0.5f,   /* Vertex 6 */    /* TexCoord */  1,1,
		-0.5f,  0.5f, -0.5f,   /* Vertex 7 */    /* TexCoord */  0,1
	};

	const std::vector<GLuint> indices =
	{
		// Front face
		0, 1, 2,
		2, 3, 0,

		// Back face
		4, 5, 6,
		6, 7, 4,

		// Left face
		7, 3, 0,
		0, 4, 7,

		// Right face
		6, 2, 1,
		1, 5, 6,

		// Top face
		0, 1, 5,
		5, 0, 4,

		// Bottom face
		3, 2, 6,
		6, 7, 3
	};

	player = new Player(rRunning);
	
	auto left = new Mesh(vertData, indices);
	auto right = new Mesh(vertData, indices);
	auto back = new Mesh(vertData, indices);
	auto floor1 = new Mesh(vertData, indices);
	
	auto box1 = new Mesh(vertData, indices);
	auto box2 = new Mesh(vertData, indices);
	auto box3 = new Mesh(vertData, indices);
	auto box4 = new Mesh(vertData, indices);
	
	left->SetScale(.2f, 15, 15);
	left->AddPosition(-7.5f, 0,0);

	right->SetScale(.2f, 15, 15);
	right->AddPosition(7.5f, 0,0);
	
	back->SetScale(15, 15, .2f);
	back->AddPosition(0, 0, 7.5f);
	
	floor1->AddPosition(0, 10.5, 0);
	floor1->SetScale(100, 8, 400);

	model = new Model("ModelAssets/Barrel.obj");
	model->AddPosition(0,5,-10);

	box1->SetPosition(30,10,30);
	
	meshes =
	{
		left, right, back, floor1, box1, box2, box3, box4
	};

	box2->AddPosition(0, 5, 0);

	player->SetLevelMeshes(meshes);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Game::Update(float deltaTime) const
{
	player->Update(deltaTime);
	
	if (meshes[5])
	{
		meshes[5]->AddPosition(.5f * deltaTime, 0,0);
		meshes[5]->AddRotation(0, .005f * deltaTime, 0);
	}
	if(model) model->AddRotation(0, .005f * deltaTime, 0);

}

void Game::FixedUpdate(float deltaTime)
{
	player->FixedUpdate(deltaTime);
}

void Game::Render() const
{
	glClearColor(.04f, .01f, .1f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	player->Render();
	
	for (const auto& mesh : meshes)
	{
		if(mesh) mesh->Render(player->GetCamera());
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(model) model->Render(player->GetCamera());
	
	SDL_GL_SwapWindow(window);
}
