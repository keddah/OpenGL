#include "Shader.h"

void Shader::MakeShader()
{
	const char* vShaderSource[] = { "#version 140\n"
		"in vec2 vertexPos2D;\n"
		"void main() { \n"
		"gl_Position = vec4(vertexPos2D.xy, 0, 1);\n"
		"}"
	};
	const char* fShaderSource[] = { "#version 140\n"
	"uniform vec3 colour;"
	"out vec4 fragmentColor;\n"
	"void main() { \n"
	"fragmentColor = vec4(colour.xyz, 1.0);\n"
	"}"
	};

	program_id = glCreateProgram();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, vShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint successful = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successful);

	if (successful != GL_TRUE)
	{
		print("couldn't compile vertex shader.")
			GLsizei len;
		char error[1500];
		glGetShaderInfoLog(vertexShader,
				1500,
				&len,
				error);
			print(error)
			print(glGetError())
			return;
	}


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, fShaderSource, NULL);
	glCompileShader(fragmentShader);

	successful = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successful);
	if (successful != GL_TRUE)
	{
		print("couldn't compile fragment shader.")
			return;
	}

	glAttachShader(program_id, vertexShader);
	glAttachShader(program_id, fragmentShader);
	glLinkProgram(program_id);
	if (successful != GL_TRUE)
	{
		print("couldn't link program...")
			return;
	}
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}