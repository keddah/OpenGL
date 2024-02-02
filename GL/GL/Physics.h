#pragma once
#include <glm.hpp>
#include <iostream>

#define print(x) { std::cout << x << std::endl; }

class Physics
{
public:
    glm::vec3 GetVelocity() const { return velocity; }
    bool IsGrounded() const { return grounded; }
    void SetGrounded(const bool newValue) { grounded = newValue; }
    void SetCollided(const bool collided) { if(collided) velocity = {}; }
    
protected:
    void ApplyGravity();
    
    glm::vec3 velocity = {};
    bool grounded = false;
    
private:
    const float gravity = 9.8f;
    const float acceleration = 2.0f;
    const float drag = 1.0f;

    const float maxFallSpeed = 3000;
    const float maxSpeed = 400;
};
