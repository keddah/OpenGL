#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Controller.h"

struct AngleConversion
{
	static glm::vec3 eulerToQuaternion(const float pitch, const float yaw, const float roll)
	{
		return {glm::radians(pitch), glm::radians(yaw), glm::radians(roll)};
	}
};

class Camera
{
public:
	Camera(Controller& roller); 

	// void Update(float deltaTime) { }
	void Look(glm::vec2 mouseDelta, float deltaTime);
	void UpdateViewMatrix() { viewMatrix = glm::lookAt(position, forwardVector + position, glm::vec3(0,1,0)); }

	glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }
	glm::mat4 GetViewMatrix() const { return viewMatrix; }
	
	void SetPosition(const glm::vec3 pos) { position = pos; }
	void SetPosition(const float x, const float y, const float z) { position = glm::vec3(x, y, z); }
	glm::vec3 GetPosition() const { return position; }

	glm::vec3 GetForwardVector() const { return normalize(forwardVector); }
	glm::vec3 GetRightVector() const { return normalize(rightVector); }
	float GetPitch() const { return pitch; }
	
private:
	const float fov = 65.0f;
	const float aspectRatio = 1920 / 1080;
	const float nearClip = .1f;
	const float farClip = 600;
	
	float pitch, yaw;
	const float maxPitch = 87;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	// X = left/right
	// Y = up/down
	// Z = forwards/backwards
	glm::vec3 position;
	glm::vec3 forwardVector;
	glm::vec3 rightVector;

	Controller& control;
};

