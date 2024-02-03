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

	// Stop the player from moving and remove velocity
	void SetCollided(const bool collided)
	{
		if(collided)
		{
			canMove = false;
			velocity = glm::vec3(0, velocity.y, 0);
		}

		else
		{
			canMove = true;
		}
	}

	void Render() { wc.Render(); }

	Camera& GetCamera() const { if(!cam) print("unable to get Cam") return *cam; }

	glm::vec3 GetPosition() const { return position; }
	float GetPlayerHeight() const { return playerHeight; }
	BoundingBox GetBounds() const { return playerBounds; }
	
private:
	void Accelerate(float deltaTime);
	void Decelerate(float deltaTime);
	void Jump();
	void Crouch();
	void Collisions();

	bool accelerating;
	bool canMove = true;
	glm::vec3 position = { 0, -5, 1.5f};

	Controller controller;
	Camera* cam;

	const float playerHeight = 2;
	const float walkSpeed = .2f;
	const float sprintSpeed = 2;

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

