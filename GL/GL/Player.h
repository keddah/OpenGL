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
	
	glm::vec3 position;

	Controller controller;
	Camera* cam;
	
	const float walkSpeed = .2f;
	const float sprintSpeed = .8f;


	
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

