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
    const glm::vec3 terminalVelocity {100, 1000, 100};
    bool grounded = false;
    
    const float acceleration = .04f;

    // Lateral (side-to-side) acceleration
    const float latAcceleration = .06f;
    const float drag = .08f;
    
private:
    const float gravity = 9.8f;
};
