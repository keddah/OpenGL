#pragma once
#include "Mesh.h"
#include <SDL_image.h>
#include <vector>

class Terrain 
{
public:
	Terrain(const std::string& heightPath);
	void Render(Camera* cam, const Light& light) const { if(floor) floor->Render(cam, light); }

	
	Mesh* GetMesh() const { return floor; }

	void SetPosition(const glm::vec3& newVal) const { floor->SetPosition(newVal); }
	void SetPosition(const float x, const float y, const float z) const { floor->SetPosition(x,y,z); }

	void AddPosition(const glm::vec3& newVal) const { floor->AddPosition(newVal); }
	void AddPosition(const float x, const float y, const float z) const { floor->AddPosition(x,y,z); }
    
	void SetRotation(const glm::vec3& newVal) const { floor->SetRotation(newVal); }
	void SetRotation(const float x, const float y, const float z) const { floor->SetRotation(x,y,z); }
    
	void AddRotation(const glm::vec3& newVal) const { floor->AddRotation(newVal); }
	void AddRotation(const float x, const float y, const float z) const { floor->AddRotation(x,y,z); }
    
	void SetScale(const glm::vec3& newVal) const { floor->SetScale(newVal); }
	void SetScale(const float x, const float y, const float z) const { floor->SetScale(x,y,z); }
	void SetScale(const float xyz) const { floor->SetScale(xyz,xyz,xyz); }

	void SetUvScale(const glm::vec3& uv) const { floor->SetUvScale(uv); }
	void SetUvScale(const float u, const float v) const { floor->SetUvScale(u,v); }

	glm::vec3 GetPosition() const { return floor->GetPosition(); }
	
private:
	Mesh* floor;


};