/**************************************************************************************************************
* Camera - Header
*
* The header file for the Camera class. Responsible for providing get functions for the player class so that
* it can read inputs (everything is private). 
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


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
	void UpdateViewMatrix() { viewMatrix = glm::lookAt(position, forwardVector + position, glm::vec3(0,1,0)); }

	glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }
	glm::mat4 GetViewMatrix() const { return viewMatrix; }
	
	void SetPosition(const glm::vec3 pos) { position = pos; }
	void SetPosition(const float x, const float y, const float z) { position = glm::vec3(x, y, z); }
	glm::vec3 GetPosition() const { return position; }

	glm::vec3 GetForwardVector() const { return normalize(forwardVector); }
	glm::vec3 GetRightVector() const { return normalize(rightVector); }
	glm::vec3 GetUpVector() const { return normalize(upVector); }
	float GetPitch() const { return pitch; }
	
private:
	const float fov = 65.0f;
	float aspectRatio;
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
	glm::vec3 forwardVector, rightVector, upVector;

	Controller& control;
};

