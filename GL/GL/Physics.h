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
    void ApplyGravity();
    
    glm::vec3 velocity = {};
    const glm::vec3 terminalVelocity {100, 1000, 100};
    bool grounded = false;
    
    const float walkAccel = .04f;
    const float sprintAccel = walkAccel * 3.5f;

    // Lateral (side-to-side) acceleration
    const float latAcceleration = .06f;
    const float drag = .08f;
    
private:
    const float gravity = .05f;
};
