/**************************************************************************************************************
* Terrain - Code
*
* Creates a plane based off of a height map texture then changes the position of the vertices of the plane to reproduce the map.
* The plane is created using the number of pixels the image has. 
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#include "Terrain.h"

Terrain::Terrain(const std::string& heightPath) 
{
	SDL_Surface* heightMap = IMG_Load(heightPath.c_str());
	if(!heightMap)
	{
		print("Unable to load image - possible bad filePath")
		return;
	}
	
	const int height = heightMap->h;
	const int width = heightMap->w;
	const unsigned char* imageData = (unsigned char*)heightMap->pixels;
	const int channels = heightMap->format->BytesPerPixel;
	constexpr float heightScaling = 10.0f;
	constexpr float scaling = 100.0f;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	
	for (int row = 0; row < height; row++)
	{
		for (int column = 0; column < width; column++)
		{
			const unsigned char redPixel = imageData[((row * width) + column) * channels];

			// Setting the position of the vertices depending on the value of the current pixel in the map
			const float x = (float)column / (float)(width - 1) * scaling;
			const float z = (float)row / (float)(height - 1) * scaling;
			const float y = (float)redPixel / 255.0f * heightScaling;

			// Setting the UV 
			const float u = (float)column / (float)(width - 1);
			const float v = (float)(height - row) / (float)(height - 1);

			// Position
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// Normals
			vertices.push_back(0);
			vertices.push_back(0);
			vertices.push_back(0);

			// UV
			vertices.push_back(u);
			vertices.push_back(v);
		}
	}

	// Producing the indices for the plane
	for (int row = 0; row < height - 1; row++)
	{
		for (int column = 0; column < width - 1; column++)
		{
			const unsigned int c = row * width + column;
			const unsigned int n = (row + 1) * width + column;

			indices.push_back(c);
			indices.push_back(n);
			indices.push_back(c + 1);
			indices.push_back(c + 1);
			indices.push_back(n);
			indices.push_back(n + 1);
		}
	}

	// Create a mesh from the vertex data and the vertices
	const std::vector<std::string>& floorTex = {"Images/gravelBaseColour.jpg", "Images/gravelNormal.jpg"};
	floor = new Mesh(vertices, indices, floorTex);	

	SDL_FreeSurface(heightMap);
}