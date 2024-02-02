#pragma once
#include "Camera.h"
#include <glm.hpp>

#include "Physics.h"

class Player : public Physics
{
public:
	Player(bool running);
	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);

	void Render() { wc.Render(); }

	Camera& GetCamera() const { return *cam; }
	
private:
	void Move(float deltaTime);
	void Jump();
	void Crouch();
	void Collisions();
	
	glm::vec3 position;

	Controller controller;
	Camera* cam;
	
	const float walkSpeed = .2f;
	const float sprintSpeed = .8f;

	// 0 = min ... 1 = max
	const glm::vec3 playerBounds[2] =
	{
		{-.25f, -1, -.25f},
		{.25f, 1, .25f}
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

