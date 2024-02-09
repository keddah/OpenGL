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
	// Always Base colour  -->  Normal
	Model(const string& meshPath, string materialPaths[] = new string {"Images/Barrel_d.png"});
	~Model() { delete gameMesh; }

	void Render(Camera* cam, Light light) const;

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const; 
	glm::vec3 GetScale() const;

	Transform GetTransform() const { return gameMesh->GetTransform(); }
	void SetTransform(const glm::vec3 pos, const glm::vec3 rot, const glm::vec3 scale) const { gameMesh->SetTransform(pos, rot, scale); }
	void SetTransform(const float x, const float y, const float z, glm::vec3 rot, const glm::vec3 scale) const { gameMesh->SetTransform({x,y,z}, rot, scale); }
	void SetTransform(const glm::vec3 pos, const float x, const float y, const float z, const glm::vec3 scale) const { gameMesh->SetTransform(pos, {x,y,z}, scale); }
	void SetTransform(const glm::vec3 pos, const glm::vec3 rot, const float x, const float y, const float z) const { gameMesh->SetTransform(pos, rot, {x,y,z}); }
	void SetTransform(const float px, const float py, const float pz, const float rx, const float ry, const float rz, const float sx, const float sy, const float sz) const;
	
	void SetPosition(const glm::vec3 newVal) const;
	void SetPosition(const float x, const float y, const float z) const;

	void AddPosition(const glm::vec3 newVal) const;
	void AddPosition(const float x, const float y, const float z) const;
    
	void SetRotation(const glm::vec3 newVal) const;
	void SetRotation(const float x, const float y, const float z) const;
    
	void LookAtRotation(glm::mat4 matrix);

	void AddRotation(const glm::vec3 newVal) const;
	void AddRotation(const float x, const float y, const float z) const;
    
	void SetScale(const glm::vec3 newVal) const;
	void SetScale(const float x, const float y, const float z) const;

	void CreateMaterial(const std::string texturePath[]) const;
	void SetCollisionsEnabled(bool value) const;
	void SetVisibility(bool value) const;

	Mesh* GetMesh() const { return gameMesh; }
	std::vector<Mesh*> GetMeshes() const { return gameMeshes; }

	void SetUvScale(const glm::vec2& scale) const { gameMesh->SetUvScale(scale); } 
	void SetUvScale(const float x, const float y) const { gameMesh->SetUvScale(x, y); } 
	
private:
	Mesh* gameMesh;
	std::vector<Mesh*> gameMeshes;
};

