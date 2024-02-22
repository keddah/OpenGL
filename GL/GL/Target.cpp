/**************************************************************************************************************
* Target - Code
*
* The code file for the Target class. Responsible for creating its model and managing its collisions.
* Provides responses to being shot and hitting other things in the level.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#include "Target.h"


Target::Target(const bool moving, const glm::vec3& playerPos) : moveable(moving), rPlayerPos(playerPos)
{
    const std::vector<std::string>& path = {"Images/Barrel_d.png", "Images/Barrel_n.png" };
    barrel = new Model("ModelAssets/Barrel.obj", path);
    barrel->SetScale(transform.scale);

    // The bounding box is always too low for this target.. moving it higher.
    barrel->SetBBOffset({0, -.9f, 0});

    terminalVelocity = {.35f, .35f, .35f};
    
    Relocate();
    RandomDirection();
}

void Target::Update(float deltaTime)
{
    Timers(deltaTime);
}

void Target::FixedUpdate(float deltaTime)
{
    Move();
    Decelerate(); 

    Collisions();
    
    // The maximum distance a target is allowed to be from the player..
    constexpr float maxDistance = 65;
    
    // Prevent the targets from moving if they move too far away from the player
    far = distance(rPlayerPos, transform.position) > maxDistance;

    // Speed up if far away
    moveSpeed = far? 1.5f : .5f;

    // Limit how fast the targets can go
    if(abs(velocity.x) >= terminalVelocity.x) velocity.x = velocity.x > 0? terminalVelocity.x : -terminalVelocity.x;
    if(abs(velocity.y) >= terminalVelocity.y) velocity.y = velocity.y > 0? terminalVelocity.y : -terminalVelocity.y;
    if(abs(velocity.z) >= terminalVelocity.z) velocity.z = velocity.z > 0? terminalVelocity.z : -terminalVelocity.z;
    
    transform.position += velocity;
    
    // If the target gets too far from the player move to the player (if it's moveable) otherwise teleport near the player.
    if(far && moveable) moveDir = normalize(rPlayerPos - transform.position);
    else if(far && !moveable) Relocate();

    // If the target goes under the map... fix it.
    constexpr short heightLimit = 8;
    if(transform.position.y > heightLimit) transform.position.y = heightLimit;
    
    // Set position/rotation
    barrel->SetRotation(transform.rotation);
    barrel->SetPosition(transform.position);
}

void Target::Relocate()
{
    // Set the position of the target to a random position around the player
    const glm::vec3 randomOffset = glm::ballRand(relocateRadius);
    transform.position = rPlayerPos + randomOffset + glm::vec3(0, 3, 0);
}

void Target::Move()
{
    // Doesn't need deltaTime since it's run in FixedUpdate
    constexpr float rotSpeed = .001f;
    
    // Slowly rotate the object.
    transform.rotation = mix(transform.rotation, transform.rotation + moveDir, rotSpeed);
    
    if(!moveable) return;

    velocity += moveDir * moveSpeed;
}

void Target::Timers(const float deltaTime)
{
    if(!changeDir)
    {
        constexpr float dirDuration = 9; 
        
        // Speed up the direction changes depending on how many direction changes there are
        float time = deltaTime + (static_cast<float>(dirChanges) * .005f);

        // So that the object doesn't eventually end up changing direction every frame (it'll barely move and jitter a lot).
        constexpr float minimumDirTime = dirDuration - .65f;
        
        if(time > minimumDirTime) time = minimumDirTime; 

        // The actual timer
        directionTimer += time;
        if(directionTimer < dirDuration) return;
        
        RandomDirection();
        dirChanges++;
        directionTimer = 0;
        changeDir = true;
    }

    if(teleport) return;

    // A random number in the range to be subtracted from the duration to add some variation
    // 5 = max
    const unsigned short num = rand() % 5 + 1;
    const float teleportDuration = 10 - num;
    
    // The actual timer
    teleportTimer += deltaTime;
    if(teleportTimer < teleportDuration) return;

    teleportTimer = 0;
    
    teleport = true;
    Relocate();
}

void Target::Collisions()
{
    if(otherMeshes.empty()) return;
    
    for(const auto& mesh : otherMeshes)
    {
        if (!mesh->IsCollisions()) continue;

        const BoundingBox meshBox = mesh->GetBoundingBox();
        const bool collided = BoundingBox::PositionInBounds(transform.position + velocity, meshBox);

        if(collided)
        {
            // Bounce
            const glm::vec3 bounceDir = normalize(transform.position - meshBox.center);
            constexpr float bounceForce = 400;
            moveDir = bounceDir;
            AddForce(bounceDir, bounceForce);
            break;
        }
    }
}

void Target::Decelerate()
{
    if(!moveable) return;

    velocity = glm::mix(velocity, minVelocity, .000002f);
}
