#pragma once
#include <glm.hpp>
#include <iostream>

#define print(x) { std::cout << x << std::endl; }

class Physics
{
public:
    glm::vec3 GetVelocity() const { return velocity; }
    bool IsGrounded() const { return grounded; }
    void SetGrounded(const bool newValue) { grounded = newValue; if(grounded) velocity.y = 0; }

    void AddForce(glm::vec3 direction, float force);
    void AddForce(float x, float y, float z, float force);
    
protected:
    void ApplyGravity(float deltaTime, bool isPlayer = false);
    
    glm::vec3 velocity = {};
    const glm::vec3 terminalVelocity {10, 1000, 10};
    bool grounded = false;
    
    const float walkAccel = .075f;
    const float sprintAccel = walkAccel * .85f;

    // Lateral (side-to-side) acceleration
    const float latAcceleration = walkAccel * .9f;
    const float drag = .135f;

    // Lower number = slower falling (positive number)
    const float floatiness = .01f;

    float gravMultiplier = 1;

private:
    const float gravity = .3f;
};
