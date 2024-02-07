#pragma once

#include <glm.hpp>

class Light
{
public:
	Light() = default;

	void SetPosition(const glm::vec3 pos) { position = pos; }
	void SetColour(const glm::vec3 col) { colour = col; }
	void SetIntensity(const float val) { intensity = val; }

	float GetIntensity() const { return intensity; }
	glm::vec3 GetPosition() const { return position; }
	glm::vec3 GetColour() const { return colour; }

private:
	glm::vec3 position = {0, 20, -10};
	float intensity = 3;
	float range;
	float falloff;

	glm::vec3 colour = { 1.0f, .9f, .8f };
};

