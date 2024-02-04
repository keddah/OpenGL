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

	const std::vector<GLfloat> verts =
	{
		-0.5f, -0.5f, -0.5f,   /* Vertex 0 */    /* Colour */ .4f, .1f, .3f, 1,    /* TexCoord */  0,0,
		 0.5f, -0.5f, -0.5f,   /* Vertex 1 */    /* Colour */ .4f, .2f, .3f, 1,    /* TexCoord */  1,0,
		 0.5f,  0.5f, -0.5f,   /* Vertex 2 */    /* Colour */ .4f, .3f, .3f, 1,    /* TexCoord */  1,1,
		-0.5f,  0.5f, -0.5f,   /* Vertex 3 */    /* Colour */ .4f, .4f, .3f, 1,    /* TexCoord */  0,1,
		-0.5f, -0.5f,  0.5f,   /* Vertex 4 */    /* Colour */ .4f, .1f, .5f, 1,    /* TexCoord */  0,0,
		 0.5f, -0.5f,  0.5f,   /* Vertex 5 */    /* Colour */ .4f, .1f, .6f, 1,    /* TexCoord */  1,0,
		 0.5f,  0.5f,  0.5f,   /* Vertex 6 */    /* Colour */ .5f, .1f, .3f, 1,    /* TexCoord */  1,1,
		-0.5f,  0.5f,  0.5f,   /* Vertex 7 */    /* Colour */ .6f, .1f, .3f, 1,    /* TexCoord */  0,1
	};

	const std::vector<GLuint> indices =
	{
		0, 1, 2,  // Front face
		2, 3, 0,
		4, 5, 6,  // Back face
		6, 7, 4,
		0, 3, 7,  // Left face
		7, 4, 0,
		1, 5, 6,  // Right face
		6, 2, 1,
		3, 2, 6,  // Top face
		6, 7, 3,
		0, 1, 5,  // Bottom face
		5, 4, 0
	};

	player = new Player(rRunning);
	
	left = new Mesh(verts, indices);
	right = new Mesh(verts, indices);
	back = new Mesh(verts, indices);
	floor = new Mesh(verts, indices);
	
	model = new Model((player->GetCamera()));

	left->SetScale(.2f, 15, 15);
	left->AddPosition(-7.5f, 0,0);

	right->SetScale(.2f, 15, 15);
	right->AddPosition(7.5f, 0,0);
	
	back->SetScale(15, 15, .2f);
	back->AddPosition(0, 0, 7.5f);
	
	floor->AddPosition(0, 7.5f, 0);
	floor->SetScale(15, .2f, 15);

	model = new Model(player->GetCamera());

	const std::vector<Mesh*> meshes =
	{
		left, right, back, floor, model->GetMesh()
	};

	player->SetLevelMeshes(meshes);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Game::Update(float deltaTime) const
{
	player->Update(deltaTime);
	
	if(left) left->Update(deltaTime);
	if(right) right->Update(deltaTime);
	if(back) back->Update(deltaTime);
	if(floor) floor->Update(deltaTime);
	
	if(model)
	{
		model->AddRotation(0, .005f * deltaTime, 0);
		model->Update(deltaTime);
	}

}

void Game::FixedUpdate(float deltaTime)
{
	player->FixedUpdate(deltaTime);
	if(left) left->FixedUpdate(deltaTime);
	if(right) right->FixedUpdate(deltaTime);
	if(back) back->FixedUpdate(deltaTime);
	if(floor) floor->FixedUpdate(deltaTime);
	if(model) model->FixedUpdate(deltaTime);

}

void Game::Render() const
{
	glClearColor(.04f, .01f, .1f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//if(tri) tri->Render();
	//if(mesh) mesh->Render();
	if(left) left->Render(player->GetCamera());
	if(right) right->Render(player->GetCamera());
	if(back) back->Render(player->GetCamera());
	if(floor) floor->Render(player->GetCamera());
	
	if(model) model->Render(player->GetCamera());
	
	SDL_GL_SwapWindow(window);
}
