#include "Physics.h"

void Physics::ApplyGravity()
{
    velocity += glm::vec3(0, 1, 0) * gravity;

    if(abs(velocity.y) > maxFallSpeed) velocity.y = maxFallSpeed;
    // if(glm::vec2(velocity.x, velocity.z).length() > maxSpeed) velocity.y = maxFallSpeed;
}
