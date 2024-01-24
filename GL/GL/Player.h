#pragma once
#include "Camera.h"
#include <glm.hpp>

class Player
{
public:

private:
	glm::vec3 position;
	Camera playerCam;

	class WeaponController
	{
	public:

	private:
		Player& r_player;
	};

	WeaponController wc;

	const float moveSpeed;

};

