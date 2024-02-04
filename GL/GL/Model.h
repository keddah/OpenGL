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

	void Render(Camera& cam) const { if (gameMesh) gameMesh->Render(cam); }
	void Update(float deltaTime) const { if (gameMesh) gameMesh->Update(deltaTime); }
	void FixedUpdate(float deltaTime) const { if (gameMesh) gameMesh->FixedUpdate(deltaTime); }


	void SetPosition(const glm::vec3 newVal) const { gameMesh->SetPosition(newVal); }
	void SetPosition(const float x, const float y, const float z) const { gameMesh->SetPosition(x,y,z); }

	void AddPosition(const glm::vec3 newVal) const { gameMesh->AddPosition(newVal); }
	void AddPosition(const float x, const float y, const float z) const { gameMesh->AddPosition(x,y,z); }
    
	void SetRotation(const glm::vec3 newVal) const { gameMesh->SetRotation(newVal); }
	void SetRotation(const float x, const float y, const float z) const { gameMesh->SetRotation(x,y,z); }
    
	void AddRotation(const glm::vec3 newVal) const { gameMesh->AddRotation(newVal); }
	void AddRotation(const float x, const float y, const float z) const { gameMesh->AddRotation(x,y,z); }
    
	void SetScale(const glm::vec3 newVal) const { gameMesh->SetScale(newVal); }
	void SetScale(const float x, const float y, const float z) const { gameMesh->SetScale(x,y,z); }


	Mesh* GetMesh() const { return gameMesh; }
	
private:
	string filePath = "ModelAssets/Barrel.obj";

	Mesh* gameMesh;
	Camera& camera;
};

