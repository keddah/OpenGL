#include "Shader.h"
#include "Utilities.h"

void Shader::Init()
{
	const string verText = Util::ReadFile("Rendering/Shaders/VertexShader.glsl");
	const GLchar* vShaderSource = verText.c_str();
	
	const string fragText = Util::ReadFile("Rendering/Shaders/FragmentShader.glsl");
	const GLchar* fShaderSource = fragText.c_str();
	
	print(vShaderSource)
	print(fShaderSource)
	
	// Create the program
	program_id = glCreateProgram();

	// Create the Vertex shader.
	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Assign the vertex shader its code then compile it.
	glShaderSource(vertexShader, 1, &vShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint successful = GL_FALSE;

	// Check if the Vertex shader compiled successfully
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successful);
	if (successful != GL_TRUE)
	{
		print("couldn't compile vertex shader.")
		Util::PrintShaderLog(vertexShader);
		return;
	}
	
	// Create the Fragment shader
	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Giving the created shader its shader code then compiles it.
	glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check if the shader was successfully compiled
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successful);
	if (successful != GL_TRUE)
	{
		print("couldn't compile fragment shader.")
		Util::PrintShaderLog(fragmentShader);
		return;
	}

	// Attach the Vertex and Fragment shader to the program (connect the shaders to one thing)
	glAttachShader(program_id, vertexShader);
	glAttachShader(program_id, fragmentShader);
	glLinkProgram(program_id);

	// Check if the program successfully linked the fragment and vertex shaders
	glGetProgramiv(program_id, GL_LINK_STATUS, &successful);
	if (successful != GL_TRUE)
	{
		print("Couldn't link program...\n");
		Util::PrintProgramLog(program_id);
	}

	// Since the shaders are already on the program, you don't need the actual shaders anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}