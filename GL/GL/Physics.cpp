#include "Physics.h"

void Physics::AddForce(const glm::vec3 direction, const float force)
{
    velocity += direction * force;

    if(abs(velocity.x) >= terminalVelocity.x) velocity.x = velocity.x > 0? terminalVelocity.x : -terminalVelocity.x;
    if(abs(velocity.y) >= terminalVelocity.y) velocity.y = velocity.y > 0? terminalVelocity.y : -terminalVelocity.y;
    if(abs(velocity.z) >= terminalVelocity.z) velocity.z = velocity.z > 0? terminalVelocity.z : -terminalVelocity.z;
}

void Physics::AddForce(const float x, const float y, const float z, const float force)
{
    velocity += glm::vec3(x,y,z) * force;

    if(abs(velocity.x) >= terminalVelocity.x) velocity.x = velocity.x > 0? terminalVelocity.x : -terminalVelocity.x;
    if(abs(velocity.y) >= terminalVelocity.y) velocity.y = velocity.y > 0? terminalVelocity.y : -terminalVelocity.y;
    if(abs(velocity.z) >= terminalVelocity.z) velocity.z = velocity.z > 0? terminalVelocity.z : -terminalVelocity.z;
}

void Physics::ApplyGravity()
{
    if(grounded)
    {
        velocity.y = 0;
        return;
    }
    
    velocity += glm::vec3(0, 1, 0) * gravity;

    if(abs(velocity.y) > terminalVelocity.y) velocity.y = terminalVelocity.y;
    // if(glm::vec2(velocity.x, velocity.z).length() > maxSpeed) velocity.y = maxFallSpeed;
}
