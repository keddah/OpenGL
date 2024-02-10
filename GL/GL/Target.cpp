#include "Target.h"


Target::Target(const bool moving, const glm::vec3& playerPos) : moveable(moving), rPlayerPos(playerPos)
{
    std::string path[] = {"Images/Barrel_d.png", "Images/Barrel_n.png" };
    barrel = new Model("ModelAssets/Barrel.obj", path);
}

void Target::Update(float deltaTime)
{
    Timers(deltaTime);
}

void Target::FixedUpdate(float deltaTime)
{
    Move();
    
    // If the target goes under the map... fix it.
    if(transform.position.y > 10) transform.position.y = 10;
}

void Target::Relocate()
{
    // Set the position of the target to a random position around the player
    const glm::vec3 randomOffset = glm::ballRand(relocateRadius);
    transform.position = rPlayerPos + randomOffset;
}

void Target::Move()
{
    if(!moveable) return;

    // Doesn't need deltaTime since it's run in FixedUpdate
    constexpr float rotSpeed = .001f;
    
    // Slowly rotate the object.
    transform.rotation = mix(transform.rotation, transform.rotation + moveDir, rotSpeed);
    transform.position += moveDir * moveSpeed;

    barrel->SetPosition(transform.position);
    barrel->SetRotation(transform.rotation);
}

void Target::Timers(const float deltaTime)
{
    if(!changeDir)
    {
        constexpr float dirDuration = 9; 
        
        // Speed up the direction changes depending on how many direction changes there are
        float time = deltaTime + (static_cast<float>(dirChanges) * .0001f);

        // So that the object doesn't eventually end up changing direction every frame (it'll barely move and jitter a lot).
        constexpr float minimumDirTime = dirDuration - .65f;
        
        if(time > minimumDirTime) time = minimumDirTime; 

        // The actual timer
        directionTimer += time;
        if(directionTimer < dirDuration) return;
        
        RandomDirection();
        dirChanges++;
        changeDir = true;
    }

    if(teleport) return;

    constexpr float teleportDuration = 10;
    
    // The actual timer
    teleportTimer += deltaTime;
    if(teleportTimer < teleportDuration) return;
    
    teleport = true;
    Relocate();
}
