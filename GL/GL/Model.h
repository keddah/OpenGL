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
	Model(string filePath);
	~Model() { delete gameMesh; }

	void Render(Camera* cam) const { if (gameMesh) gameMesh->Render(cam); }

	glm::vec3 GetPosition() const { return gameMesh->GetPosition(); }

	Transform GetTransform() const { return gameMesh->GetTransform(); }
	void SetTransform(const glm::vec3 pos, const glm::vec3 rot, const glm::vec3 scale) const { gameMesh->SetTransform(pos, rot, scale); }
	void SetTransform(const float x, const float y, const float z, glm::vec3 rot, const glm::vec3 scale) const { gameMesh->SetTransform({x,y,z}, rot, scale); }
	void SetTransform(const glm::vec3 pos, const float x, const float y, const float z, const glm::vec3 scale) const { gameMesh->SetTransform(pos, {x,y,z}, scale); }
	void SetTransform(const glm::vec3 pos, const glm::vec3 rot, const float x, const float y, const float z) const { gameMesh->SetTransform(pos, rot, {x,y,z}); }
	void SetTransform(const float px, const float py, const float pz, const float rx, const float ry, const float rz, const float sx, const float sy,  const float sz) const
	{
		gameMesh->SetTransform({px,py,pz}, {rx,ry,rz}, {sx,sy,sz});
	}
	
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

	void SetCollisionsEnabled(const bool value) const { gameMesh->SetCollision(value); }
	void SetVisibility(const bool value) const { gameMesh->SetVisibility(value); }

	Mesh* GetMesh() const { return gameMesh; }

private:
	Mesh* gameMesh;
};

