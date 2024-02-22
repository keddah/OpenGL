/**************************************************************************************************************
* Model - Header
*
* Responsible for keeping track of imported models. Some models contain several meshes. It's responsible for creating an easy path for other classes
* to set transforms and material related things to each mesh of model. The difference between a mesh and a model in this project:
* Models are imported and are made up of Meshes. Meshes contain the vertex data; models import that data.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


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
	Model(const string& meshPath, const std::vector<std::string>& materialPaths = {"Images/defaultTexture.jpg"});

	// Delete all the game mesh (if there's more than one, gameMesh would be empty ... delete all the meshes in the vector and empty it.
	~Model() { if(gameMesh) delete gameMesh; else for(const auto& mesh: gameMeshes) delete mesh; gameMeshes.clear(); }

	void Render(const Camera* cam, const Light& light) const;

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const; 
	glm::vec3 GetScale() const;

	Transform GetTransform() const { return gameMesh->GetTransform(); }
	void SetTransform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) const { gameMesh->SetTransform(pos, rot, scale); }
	void SetTransform(const float x, const float y, const float z, const glm::vec3& rot, const glm::vec3& scale) const { gameMesh->SetTransform({x,y,z}, rot, scale); }
	void SetTransform(const glm::vec3& pos, const float x, const float y, const float z, const glm::vec3& scale) const { gameMesh->SetTransform(pos, {x,y,z}, scale); }
	void SetTransform(const glm::vec3& pos, const glm::vec3& rot, const float x, const float y, const float z) const { gameMesh->SetTransform(pos, rot, {x,y,z}); }
	void SetTransform(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz) const;
	
	void SetPosition(const glm::vec3& newVal) const;
	void SetPosition(float x, float y, float z) const;

	void AddPosition(const glm::vec3& newVal) const;
	void AddPosition(float x, float y, float z) const;
    
	void SetRotation(const glm::vec3& newVal) const;
	void SetRotation(float x, float y, float z) const;
    
	void LookAtRotation(const glm::mat4& matrix) const;

	void AddRotation(const glm::vec3& newVal) const;
	void AddRotation(float x, float y, float z) const;
    
	void SetScale(const glm::vec3& newVal) const;
	void SetScale(float x, float y, float z) const;
	void SetScale(float xyz) const;

	void CreateMaterial(const std::vector<std::string>& texturePath) const;
	void SetCollisionsEnabled(bool value) const;
	void SetVisibility(bool value) const;

	void SetBBOffset(const glm::vec3& offset) const;
	
	Mesh* GetMesh() const { return gameMesh; }
	std::vector<Mesh*> GetMeshes() const { return gameMeshes; }

	void SetUvScale(const glm::vec2& scale) const; 
	void SetUvScale(float x, float y) const;

private:
	Mesh* gameMesh;
	std::vector<Mesh*> gameMeshes;
};

