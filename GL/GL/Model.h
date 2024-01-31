#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm.hpp>

#include <vector>
#include <string>
#include "Mesh.h"

using namespace std;


class Model
{
public:
	Model(Camera& cam);
	~Model() { delete gameMesh; }

	void Render() const { if (gameMesh) gameMesh->Render(); }
	void Update(float deltaTime) { if (gameMesh) gameMesh->Update(deltaTime); }

private:
	string filePath = "ModelAssets/Barrel.obj";

	Mesh* gameMesh;
};

