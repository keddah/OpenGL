#include "Player.h"

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

    Move(deltaTime);
    cam->SetPosition(position);
    position += velocity;
}

void Player::Move(float deltaTime)
{
    const bool* inputs = controller.GetMoveInputs();

    // Not using else ifs so that multiple inputs can happen at the same time
    // Forward/Backward
    if(inputs[0]) position += walkSpeed * cam->GetLookAt();
    if(inputs[1]) position -= walkSpeed * cam->GetLookAt();

    // Strafing
    if (inputs[2]) position += normalize(cross(cam->GetLookAt(), glm::vec3(0.0f, 1.0f, 0.0f))) * walkSpeed;  // Strafe left
    if (inputs[3]) position -= normalize(cross(cam->GetLookAt(), glm::vec3(0.0f, 1.0f, 0.0f))) * walkSpeed;  // Strafe right

    if(controller.JumpBtnDown()) Jump();
    if(controller.CrouchBtnDown()) Crouch();
}

void Player::Jump()
{
    position.y -= walkSpeed;
}

void Player::Crouch()
{
    position.y += walkSpeed;
}

void Player::Collisions()
{
    
}
