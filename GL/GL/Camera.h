#pragma once
#include <glm.hpp>

class Camera
{
public:
	Camera();

private:
	const float cameraHeight;

	const float fov;
	const float aspectRatio = 640 / 480;
	const float nearClip;
	const float farClip;
	
	glm::vec3 position;
};

