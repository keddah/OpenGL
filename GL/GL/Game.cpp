#include "Game.h"

Game::Game()
{
	Init();
}

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
}

void Game::triangle()
{
	constexpr GLfloat verts[] =
	{
		-.5f, .5, 0, // top left
		-.5, 0, 0, // bottom left
		.5, 0, 0 // right
	};

	shader_program = glCreateProgram();
	Shader vert_shader = Shader(shader_program, vert_shader_source);
	Shader fragment_shader = Shader(shader_program, fragment_shader_source);

	vert_shader.Delete();
	fragment_shader.Delete();

	glGenVertexArrays(1, &vert_array);
	glGenBuffers(1, &vert_buffer);

	glBindVertexArray(vert_array);

	glBindBuffer(GL_ARRAY_BUFFER, vert_buffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Game::Clean() const
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::Update(float deltaTime)
{
	triangle();
}

void Game::FixedUpdate(float deltaTime)
{
}

void Game::Render()
{
	glClearColor(.04f, .01f, .1f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// The drawing part
	glUseProgram(shader_program);
	glBindVertexArray(vert_array);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(window);
}
