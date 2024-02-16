#include "Shader.h"
#include "Utilities.h"
#include <gtc/type_ptr.hpp>

void Shader::Init()
{
	const string verText = Util::ReadFile(vertShaderPath);
	const GLchar* vShaderSource = verText.c_str();
	
	const string fragText = Util::ReadFile(fragShaderPath);
	const GLchar* fShaderSource = fragText.c_str();
	
	//print(vShaderSource)
	//print(fShaderSource)
	
	// Create the program
	program_id = glCreateProgram();

	// Create the Vertex shader.
	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Assign the vertex shader its code then compile it.
	glCall(glShaderSource(vertexShader, 1, &vShaderSource, NULL));
	glCall(glCompileShader(vertexShader));

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
	glCall(glShaderSource(fragmentShader, 1, &fShaderSource, NULL));
	glCall(glCompileShader(fragmentShader));

	// Check if the shader was successfully compiled
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successful);
	if (successful != GL_TRUE)
	{
		print("couldn't compile fragment shader.")
		Util::PrintShaderLog(fragmentShader);
		return;
	}

	// Attach the Vertex and Fragment shader to the program (connect the shaders to one thing)
	glCall(glAttachShader(program_id, vertexShader));
	glCall(glAttachShader(program_id, fragmentShader));
	glCall(glLinkProgram(program_id));

	// Check if the program successfully linked the fragment and vertex shaders
	glGetProgramiv(program_id, GL_LINK_STATUS, &successful);
	if (successful != GL_TRUE)
	{
		print("Couldn't link program...\n");
		Util::PrintProgramLog(program_id);
	}

	// Since the shaders are already on the program, you don't need the actual shaders anymore
	glCall(glDeleteShader(vertexShader));
	glCall(glDeleteShader(fragmentShader));
}

void Shader::SetFloatAttrib(const std::string& attribName, const float newValue) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());
	glCall(glUniform1f(id, newValue));
}

float Shader::GetFloatAttrib(const std::string& attribName) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());

	float value;
	glCall(glGetUniformfv(program_id, id, &value));
	return value;
}

void Shader::SetVec2Attrib(const std::string& attribName, glm::vec2 newValue) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());
	glCall(glUniform2f(id, newValue.x, newValue.y));
}

void Shader::SetVec2Attrib(const std::string& attribName, const float x, const float y) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());
	glCall(glUniform2f(id, x, y));
}

void Shader::SetVec3Attrib(const std::string& attribName, const glm::vec3 newValue) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());
	glCall(glUniform3f(id, newValue.x, newValue.y, newValue.z));
}

void Shader::SetVec3Attrib(const std::string& attribName, const float x, const float y, const float z) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());
	glCall(glUniform3f(id, x, y, z));
}

void Shader::SetVec4Attrib(const std::string& attribName, const glm::vec4 newValue) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());
	glCall(glUniform4f(id, newValue.x, newValue.y, newValue.z, newValue.w));
}

void Shader::SetVec4Attrib(const std::string& attribName, const float x, const float y, const float z, const float w) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());
	glCall(glUniform4f(id, x, y, z, w));
}

void Shader::SetMat4Attrib(const std::string& attribName, glm::mat4 newValue) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());
	glCall(glUniformMatrix4fv(id, 1, GL_FALSE, value_ptr(newValue)));
}

void Shader::SetUintAttrib(const std::string& attribName, const unsigned int newValue) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());
	glCall(glUniform1ui(id, newValue));
}

unsigned Shader::GetUintAttrib(const std::string& attribName) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());

	unsigned int value;
	glCall(glGetUniformuiv(program_id, id, &value));
	return value;
}

void Shader::SetIntAttrib(const std::string& attribName, const int newValue) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());
	glCall(glUniform1i(id, newValue));
}

int Shader::GetIntAttrib(const std::string& attribName) const
{
	const GLint id = glGetUniformLocation(program_id, attribName.c_str());

	int value;
	glCall(glGetUniformiv(program_id, id, &value));
	return value;
}
