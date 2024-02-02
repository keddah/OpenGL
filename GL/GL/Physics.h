#pragma once
#include <glm.hpp>

class Physics
{
public:
    glm::vec3 GetVelocity() const { return velocity; }
    
protected:
    void ApplyGravity();
    
    glm::vec3 velocity = {};
    
private:
    const float gravity = 9.8f;
    const float acceleration = 2.0f;
    const float drag = 1.0f;

    const float maxFallSpeed = 3000;
    const float maxSpeed = 400;
};
