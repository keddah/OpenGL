/**************************************************************************************************************
* Physics - Code
*
* Gives simple functionality to a physics system by creating AddForce functions and a Gravity function.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


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

void Physics::ApplyGravity(float deltaTime, const bool isPlayer)
{
    if(isPlayer)
    {
        if(grounded)
        {
            velocity.y = 0;
            gravMultiplier = .3f;
            return;
        }

        // Make things falls faster the longer they're in the air....
        gravMultiplier += deltaTime * floatiness;
        if(gravMultiplier > 3) gravMultiplier = 3;
    }
    
    velocity.y += gravity * gravMultiplier;

    if(abs(velocity.y) > terminalVelocity.y) velocity.y = terminalVelocity.y;
}
