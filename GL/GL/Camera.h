#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Controller.h"

class Camera
{
public:
	Camera(Controller& roller); 

	void Update() { Move(); }
	void UpdateViewMatrix() { viewMatrix = glm::lookAt(position, lookAt, glm::vec3(0,1,0)); }

	glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }
	glm::mat4 GetViewMatrix() const { return viewMatrix; }
	
	void SetPosition(glm::vec3 pos) { position = pos; }
	void SetPosition(float x, float y, float z) { position = {x, y, z}; }
	glm::vec3 GetPosition() const { return position; }

	void SetLookAt(glm::vec3 pos) { position = pos; }
	void SetLookAt(float x, float y, float z) { position = {x,y,z}; }
	glm::vec3 GetLookAt() const { return position; }
	
private:
	void Move();
	
	const float cameraHeight = 2;

	const float fov = 80;
	const float aspectRatio = 640 / 480;
	const float nearClip = .1f;
	const float farClip = 600;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	// X = left/right
	// Y = up/down
	// Z = forwards/backwards
	glm::vec3 position;
	glm::vec3 lookAt;

	Controller& control;
};

