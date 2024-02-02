#include "Physics.h"

void Physics::ApplyGravity()
{
    if(grounded) return;
    
    velocity += glm::vec3(0, 1, 0) * gravity;

    if(abs(velocity.y) > terminalVelocity.y) velocity.y = terminalVelocity.y;
    // if(glm::vec2(velocity.x, velocity.z).length() > maxSpeed) velocity.y = maxFallSpeed;
}
