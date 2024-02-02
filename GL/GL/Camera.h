#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Controller.h"

class Camera
{
public:
	Camera(Controller& roller); 

	// void Update(float deltaTime) { }
	void Look(glm::vec2 mouseDelta, float deltaTime);
	void UpdateViewMatrix() { viewMatrix = glm::lookAt(position, lookAt + position, glm::vec3(0,1,0)); }

	glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }
	glm::mat4 GetViewMatrix() const { return viewMatrix; }
	
	void SetPosition(const glm::vec3 pos) { position = pos; }
	void SetPosition(const float x, const float y, const float z) { position = glm::vec3(x, y, z); }
	glm::vec3 GetPosition() const { return position; }

	void SetLookAt(const glm::vec3 newLook) { lookAt = newLook; }
	void SetLookAt(const float x, const float y, const float z) { lookAt = glm::vec3(x,y,z); }
	glm::vec3 GetLookAt() const { return lookAt; }
	
private:
	
	const float cameraHeight = 2;

	const float fov = 80;
	const float aspectRatio = 1920 / 1080;
	const float nearClip = .1f;
	const float farClip = 600;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	// X = left/right
	// Y = up/down
	// Z = forwards/backwards
	glm::vec3 position = glm::vec3(0,0, -3);
	glm::vec3 lookAt;

	Controller& control;
};

