/**************************************************************************************************************
* Physics - Header
*
* Will be used as a inherited class for things that need to react to gravity or other forces. 
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


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
    glm::vec3 terminalVelocity {10, 1000, 10};
    bool grounded = false;
    
    const float drag = .135f;

    // Lower number = slower falling (positive number)
    const float floatiness = .01f;

    float gravMultiplier = 1;

private:
    const float gravity = .3f;
};
