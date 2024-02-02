#pragma once
#include "Camera.h"
#include <glm.hpp>
#include "BoundingBox.h"
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
	BoundingBox GetBounds() const { return playerBounds; }
	
private:
	void Move(float deltaTime);
	void Jump();
	void Crouch();
	void Collisions();
	
	glm::vec3 position = { 0, -5, 0};

	Controller controller;
	Camera* cam;
	
	const float walkSpeed = .2f;
	const float sprintSpeed = .8f;

	BoundingBox playerBounds =
	{
		{-.25f, -1, -.25f},
		{.25f, 1, .25f},
		{}
	};
	
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

