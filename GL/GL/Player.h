#pragma once
#include "Camera.h"
#include <glm.hpp>
#include <utility>
#include <vector>

#include "BoundingBox.h"
#include "Mesh.h"
#include "Physics.h"

class Player : public Physics
{
public:
	Player(bool running);
	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);

	void Render() { wc.Render(); }

	Camera& GetCamera() const { if(!cam) print("unable to get Cam") return *cam; }

	glm::vec3 GetPosition() const { return position; }
	float GetPlayerHeight() const { return playerHeight; }

	void SetLevelMeshes(const std::vector<Mesh*>& newMeshes) { meshes = newMeshes; }
	
private:
	void Accelerate(float deltaTime);
	void Decelerate(float deltaTime);
	void Jump();
	void Crouch();
	void Collisions();

	bool accelerating;
	glm::vec3 position = { 0, -5, 1.5f};

	Controller controller;
	Camera* cam;

	std::vector<Mesh*> meshes; 
	
	const float playerHeight = 3;
	const float walkSpeed = .2f;
	const float sprintSpeed = 2;

	class WeaponController
	{
	public:
		WeaponController(Player* player) : rPlayer(*player) {}
		void Update(float deltaTime) { }

		void Render() { }
		
	private:
		Player& rPlayer;
	};

	WeaponController wc = {this};


};

