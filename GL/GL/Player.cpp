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
    // ApplyGravity();

    Accelerate(deltaTime);
    Decelerate(deltaTime);
    cam->SetPosition(position);
    position += velocity;
}

void Player::Accelerate(float deltaTime)
{
    const bool* inputs = controller.GetMoveInputs();
    
    // Is sprinting?
    const bool sprinting = controller.ShiftBtnDown();
    moveSpeed = sprinting? sprintSpeed: walkSpeed;
    const float accel = sprinting? acceleration * 3.5f : acceleration;
    
    const bool forwards = inputs[0];
    const bool backwards = inputs[1];

    glm::vec3 straightAcceleration;
    if(forwards) straightAcceleration = velocity + moveSpeed * cam->GetLookAt();
    if(backwards) straightAcceleration = velocity - walkSpeed * cam->GetLookAt();
    
    // Is the new velocity trying to go in the opposite direction...
    const bool opposite = glm::dot(glm::normalize(velocity), glm::normalize(straightAcceleration)) < 0;

    // If trying to go in the opposite forward direction... use a multiplier
    constexpr float turnMultiplier = 2.2f;
    
    /////// Forwards/Backward
    if(inputs[0]) velocity = mix(velocity, straightAcceleration, opposite? accel * turnMultiplier : accel);
    if(inputs[1]) velocity = mix(velocity, straightAcceleration, opposite? acceleration * turnMultiplier : acceleration);   // Can't sprint backwards

    /////// Strafing
    const glm::vec3 strafe = normalize(cross(cam->GetLookAt(), glm::vec3(0.0f, 1.0f, 0.0f))) * walkSpeed;   // Can't increase strafe speed by sprinting

    const float strafeAcceleration = forwards || backwards? latAcceleration * .4f : latAcceleration;
    
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
    
    velocity = mix(velocity, {}, drag);
}

void Player::Jump()
{
    position.y -= moveSpeed;
}

void Player::Crouch()
{
    position.y += moveSpeed;
}

void Player::Collisions()
{
    
}
