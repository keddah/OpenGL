#include "Player.h"

#include <ext/quaternion_common.hpp>

Player::Player(bool running) : controller(running)
{
    cam = new Camera(controller);

    playerBounds.center = (playerBounds.min + playerBounds.max) * .5f;
}

void Player::Update(float deltaTime)
{
    controller.Update();
    cam->Look(controller.GetMouseDelta(), deltaTime);
    
    wc.Update(deltaTime);
}

void Player::FixedUpdate(float deltaTime)
{
    ApplyGravity();

    Accelerate(deltaTime);
    Decelerate(deltaTime);

    position += velocity;
    cam->SetPosition(position);
}

void Player::Accelerate(float deltaTime)
{
    if(!canMove)
    {
        velocity.x = 0;
        velocity.z = 0;
        return;
    }
    const bool* inputs = controller.GetMoveInputs();
    
    // Is sprinting?
    const bool sprinting = controller.ShiftBtnDown();
    const float accel = sprinting? sprintAccel : walkAccel;
    
    // If trying to go in the opposite forward direction... use a multiplier
    constexpr float turnMultiplier = 2.5f;
    
    /////// Forwards
    if(inputs[0])
    {
        const glm::vec3 straightAcceleration = velocity + (sprinting? sprintSpeed: walkSpeed) * cam->GetLookAt();
        
        // Is the new velocity trying to go in the opposite direction...
        const bool opposite = dot(normalize(velocity), normalize(straightAcceleration)) < 0;

        // velocity = mix(velocity, straightAcceleration, opposite? accel * turnMultiplier : accel);
        if(canMove)
        {
            // Only operating on the horizontal axis
            velocity.x = mix(velocity, straightAcceleration, opposite? accel * turnMultiplier : accel).x;
            velocity.z = mix(velocity, straightAcceleration, opposite? accel * turnMultiplier : accel).z;
        }

    }

    /////// Backwards
    if(inputs[1])
    {
        const glm::vec3 straightAcceleration = velocity - walkSpeed * cam->GetLookAt();

        // Is the new velocity trying to go in the opposite direction...
        const bool opposite = dot(normalize(velocity), normalize(straightAcceleration)) < 0;

        // velocity = mix(velocity, straightAcceleration, opposite? walkAccel * turnMultiplier : walkAccel);   // Can't sprint backwards

        if(canMove)
        {
            // Only operating on the horizontal axis
            velocity.x = mix(velocity, straightAcceleration, opposite? walkAccel * turnMultiplier : walkAccel).x;   // Can't sprint backwards
            velocity.z = mix(velocity, straightAcceleration, opposite? walkAccel * turnMultiplier : walkAccel).z;  
        }
    }

    /////// Strafing
    const glm::vec3 strafe = normalize(cross(cam->GetLookAt(), glm::vec3(0.0f, 1.0f, 0.0f))) * walkSpeed;   // Can't increase strafe speed by sprinting

    // If moving forwards/backwards ... decrease lateral accerlation
    const float strafeAcceleration = inputs[0] || inputs[1]? latAcceleration * .4f : latAcceleration;
    
    // Strafe Left
    if (inputs[2]) velocity = mix(velocity, strafe, strafeAcceleration);

    // Strafe Right
    if (inputs[3]) velocity = mix(velocity, -strafe, strafeAcceleration);

    accelerating = inputs[0] || inputs[1] || inputs[2] || inputs[3];
    
    if(controller.JumpBtnDown()) Jump();
    if(controller.CrouchBtnDown()) Crouch();
}

void Player::Decelerate(float deltaTime)
{
    if(accelerating) return;

    // Interpolate towards 0 velocity whilst the player isn't accelerating
    velocity = mix(velocity, {}, drag);
}

void Player::Jump()
{
    AddForce({0,-1,0}, walkSpeed);
}

void Player::Crouch()
{
    AddForce({0,1,0}, walkSpeed);
}

void Player::Collisions()
{
    
}
