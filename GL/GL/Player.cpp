/**************************************************************************************************************
* Player - Code
*
* The code file for the Player class. Responsible for giving functionality to the player. Manages player collisions, produces responses to
* player inputs, updates the camera/weapon controller.
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/

#include "Player.h"


Player::Player(bool& running) : controller(running)
{
    cam = new Camera(controller);

    position.y -= 30;
    position.z -= 5;
}

void Player::Update(float deltaTime)
{
    controller.Update();
    cam->Look(controller.GetMouseDelta(), deltaTime);
    cam->UpdateViewMatrix();

    wc.Update(deltaTime);
}

void Player::FixedUpdate(const float deltaTime)
{   
    wc.FixedUpdate(deltaTime);
    ApplyGravity(deltaTime, true);

    Accelerate();
    Decelerate();

    // Collision has to be ran after both gravity and movement so that the velocity can be set to 0 if there's a collision
    // ....COLLISIONS are unreliable when the player is moving quickly
    Collisions();

    
    position += velocity;
    cam->SetPosition(position);
}

void Player::Accelerate()
{
    const bool* inputs = controller.GetMoveInputs();
    const glm::vec2 lookat2D = { cam->GetForwardVector().x, cam->GetForwardVector().z };
    
    /////// Strafing
    const glm::vec3 strafe = strafeSpeed * cam->GetRightVector() * (inputs[2] ? 1.0f : -1.0f);

    // If moving forwards/backwards ... decrease lateral acceleration
    const float strafeAcceleration = inputs[0] || inputs[1]? latAcceleration * .4f : latAcceleration;
    
    // Strafe Left / Right
    if (inputs[2] || inputs[3])
    {
        const float yValue = velocity.y;
        velocity = mix(velocity, strafe, strafeAcceleration);

        // Ensures that the y-value is unaffected
        velocity.y = yValue;
    }


    accelerating = inputs[0] || inputs[1] || inputs[2] || inputs[3];

    if(controller.JumpBtnDown()) Jump();
    if(controller.CrouchBtnDown()) Crouch();

    
    // Shift down and not moving backwards?
    const bool sprinting = controller.ShiftBtnDown() && !inputs[1];
    const float accel = sprinting? sprintAccel : walkAccel;
    
    /////// Forwards
    if(inputs[0] || inputs[1] )
    {
        const glm::vec2 velocity2D = glm::vec2(velocity.x, velocity.z);                                                                                   // Forwards / Backwards
        const glm::vec2 moveSpeed = (sprinting? sprintSpeed: walkSpeed) * lookat2D * (inputs[0]? 1.0f : -1.0f);
        
        // Only operating on the horizontal axis
        // Lerp to the movementSpeed using acceleration as the alpha
        velocity.x = mix(velocity2D, moveSpeed, accel).x;
        velocity.z = mix(velocity2D, moveSpeed, accel).y;
    }
    
    // Cap the velocity on the x/z axis to the terminal velocity
    if(abs(velocity.x) >= terminalVelocity.x) velocity.x = velocity.x > 0? terminalVelocity.x : -terminalVelocity.x;
    if(abs(velocity.z) >= terminalVelocity.z) velocity.z = velocity.z > 0? terminalVelocity.z : -terminalVelocity.z;
}

void Player::Decelerate()
{
    // Don't decelerate if the player is trying to move
    if(accelerating) return;

    // Interpolate towards 0 velocity whilst the player isn't accelerating
    // (don't change the y value)
    velocity.x = mix(velocity, {}, drag).x;
    velocity.z = mix(velocity, {}, drag).z;
}

void Player::Jump()
{
    if(!grounded) return;
    
    AddForce({0,-1,0}, jumpForce);
}

// Was used before gravity was implemented ... (doesn't do anything now)
void Player::Crouch()
{
    if(grounded) return;
    AddForce({0,1,0}, walkSpeed);
}

void Player::Collisions()
{
    if(meshes.empty()) return;

    for(const auto& mesh : meshes)
    {
        if (!mesh->IsCollisions()) continue;

        const BoundingBox meshBox = mesh->GetBoundingBox();
        const glm::vec3 predictedPos = position + velocity;
        const glm::vec3 floorPos = { 0, predictedPos.y + playerHeight, 0 };

        const bool collided = BoundingBox::PositionInBounds(predictedPos, meshBox);

        // If there's any collision at all
        if (collided)
        {
            // So that movement is less awkward when colliding with something
            const glm::vec3 hitDirection = normalize(predictedPos - meshBox.center);
            velocity.x = hitDirection.x * .01f;
            velocity.z = hitDirection.z * .01f;
        }
        
        // Checks to see if the player lands on a y level that is equal to a collider 
        const bool hitFloor = BoundingBox::PositionInBounds(floorPos, meshBox);
        if(hitFloor)
        {
            // if it is... check if it's within the x and z values
            if(BoundingBox::PositionInBounds({predictedPos.x, predictedPos.y + playerHeight, predictedPos.z}, meshBox))
            {
                grounded = true;
                return;
            }
        }
        
    }
    
    // If no collision, reset grounded state
    grounded = false;
}
