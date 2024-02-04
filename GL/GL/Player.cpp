#include "Player.h"

#include <ext/quaternion_common.hpp>

Player::Player(bool running) : controller(running)
{
    cam = new Camera(controller);
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

    // Collision has to be ran after both gravity and movement so that the velocity can be set to 0 if there's a collision
    Collisions();

    
    position += velocity;
    cam->SetPosition(position);
}

void Player::Accelerate(float deltaTime)
{
    const bool* inputs = controller.GetMoveInputs();

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
        // Only operating on the horizontal axis
        velocity.x = mix(velocity, straightAcceleration, opposite? accel * turnMultiplier : accel).x;
        velocity.z = mix(velocity, straightAcceleration, opposite? accel * turnMultiplier : accel).z;

    }   

    /////// Backwards
    if(inputs[1])
    {
        const glm::vec3 straightAcceleration = velocity - walkSpeed * cam->GetLookAt();

        // Is the new velocity trying to go in the opposite direction...
        const bool opposite = dot(normalize(velocity), normalize(straightAcceleration)) < 0;

        // velocity = mix(velocity, straightAcceleration, opposite? walkAccel * turnMultiplier : walkAccel);   // Can't sprint backwards

        // Only operating on the horizontal axis
        velocity.x = mix(velocity, straightAcceleration, opposite? walkAccel * turnMultiplier : walkAccel).x;   // Can't sprint backwards
        velocity.z = mix(velocity, straightAcceleration, opposite? walkAccel * turnMultiplier : walkAccel).z;  
    }

    // Cap the velocity on the x/z axis to the terminal velocity
    if(abs(velocity.x) >= terminalVelocity.x) velocity.x = velocity.x > 0? terminalVelocity.x : -terminalVelocity.x;
    if(abs(velocity.z) >= terminalVelocity.z) velocity.z = velocity.z > 0? terminalVelocity.z : -terminalVelocity.z;
}

void Player::Decelerate(float deltaTime)
{
    if(accelerating) return;

    // Interpolate towards 0 velocity whilst the player isn't accelerating
    velocity = mix(velocity, {}, drag);
}

void Player::Jump()
{
    // if(!grounded) return;
    AddForce({0,-1,0}, walkSpeed);
}

void Player::Crouch()
{
    // if(!grounded) return;
    AddForce({0,1,0}, walkSpeed);
}

void Player::Collisions()
{
    if(meshes.empty()) return;
    
    for(const auto& mesh : meshes)
    {
        if (!mesh->IsCollisions()) continue;
    
        const BoundingBox meshBox = mesh->GetBoundingBox();
        const glm::vec3 predictedPos = glm::vec3(position.x , position.y + playerHeight, position.z) + velocity;
        const glm::vec3 wallPos = { predictedPos.x, 0, predictedPos.z };
        const glm::vec3 floorPos = { 0, predictedPos.y, 0 };
    
        const bool collided = BoundingBox::PositionInBounds(predictedPos, meshBox.min, meshBox.max);
        
        // Handle wall collisions
        const bool hitWall = BoundingBox::PositionInBounds(wallPos, meshBox.min, meshBox.max);
    
        // Check for floor
        const bool hitFloor = BoundingBox::PositionInBounds(floorPos, meshBox.min, meshBox.max);
        if(hitFloor && collided)
        {
            grounded = true;
            return;
        }
        
        // If there's any collision at all
        if (hitWall)
        {
            velocity = glm::vec3(0, velocity.y, 0);
    
            return; // Return early if there's a collision
        }
    }
    
    // If no collision, reset grounded state
    grounded = false;
}
