#pragma once
#include "Camera.h"
#include "Rendering/Shader.h"

#include <SDL_opengl.h>
#include <stdio.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>


#define print(x) { std::cout << x << std::endl; }


class TriangleRenderer
{
public:
	TriangleRenderer(Camera& camera) : rCam(camera) { Init(); }
	~TriangleRenderer() { Clean(); }

	void Update();
	void Render() const;
	void Clean() const
	{
		glDeleteBuffers(1, &vertex_buffer);
		glDeleteProgram(shader.GetID());
	}

private:
	void Init() { if(InitShaders()) InitVertices(); }
	bool InitShaders();
	void InitVertices();

	GLfloat vertices[9] =
	{
		0, .5f, 0,// top
		-.5f, -.5f, 0,// bottom left
		.5f, -.5, 0// bottom right
	};

	GLint vertArrayIndex = -1;

	// VertexBuffer* vBuffer;
	// IndexBuffer* iBuffer;
	
	GLuint vertex_buffer;
	GLuint index_buffer;

	Shader shader {"Rendering/Shaders/VertexShader.glsl", "Rendering/Shaders/FragmentShader.glsl"};
	float colourWave = 0;

	Camera& rCam;
	
	GLint model_matrix_address = -1;
	GLint view_matrix_address = -1;
	GLint projection_matrix_address = -1;

};

