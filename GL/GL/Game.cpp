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
}

void Game::InitOpenGL()
{
	// Make the OpenGL stuff
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
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

	std::vector<GLfloat> verts =
	{
		-0.5f, -0.5f, -0.5f,   /* Vertex 0 */    /* Colour */ .4f, .1f, .3f, 1,    /* TexCoord */  0,0,
		 0.5f, -0.5f, -0.5f,   /* Vertex 1 */    /* Colour */ .4f, .2f, .3f, 1,    /* TexCoord */  1,0,
		 0.5f,  0.5f, -0.5f,   /* Vertex 2 */    /* Colour */ .4f, .3f, .3f, 1,    /* TexCoord */  1,1,
		-0.5f,  0.5f, -0.5f,   /* Vertex 3 */    /* Colour */ .4f, .4f, .3f, 1,    /* TexCoord */  0,1,
		-0.5f, -0.5f,  0.5f,   /* Vertex 4 */    /* Colour */ .4f, .1f, .5f, 1,    /* TexCoord */  0,0,
		 0.5f, -0.5f,  0.5f,   /* Vertex 5 */    /* Colour */ .4f, .1f, .6f, 1,    /* TexCoord */  1,0,
		 0.5f,  0.5f,  0.5f,   /* Vertex 6 */    /* Colour */ .5f, .1f, .3f, 1,    /* TexCoord */  1,1,
		-0.5f,  0.5f,  0.5f,   /* Vertex 7 */    /* Colour */ .6f, .1f, .3f, 1,    /* TexCoord */  0,1,
	};

	std::vector<GLuint> indices =
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

	// std::vector<GLuint> indices =
	// {
	// 	0, 1, 2,  // Front face
	// 	2, 7, 0,
	// 	8, 9, 10,  // Back face
	// 	10, 11, 8,
	// 	0, 7, 11,  // Left face
	// 	11, 8, 0,
	// 	1, 9, 10,  // Right face
	// 	10, 2, 1,
	// 	7, 2, 10,  // Top face
	// 	10, 11, 7,
	// 	0, 1, 9,  // Bottom face
	// 	9, 10, 0
	// };
	
	mesh = new Mesh(verts, indices, cam);
}

void Game::Update(float deltaTime)
{
	mesh->Update(deltaTime);
	controller.Update();
	cam.Update();
}

void Game::FixedUpdate(float deltaTime)
{
}

void Game::Render() const
{
	glClearColor(.04f, .01f, .1f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	if(tri) tri->Render();
	if(mesh) mesh->Render();
	
	SDL_GL_SwapWindow(window);
}
