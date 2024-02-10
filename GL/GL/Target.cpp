#include "Target.h"


Target::Target(const bool moving, const glm::vec3& playerPos) : moveable(moving), rPlayerPos(playerPos)
{
    std::string path[] = {"Images/Barrel_d.png", "Images/Barrel_n.png" };
    barrel = new Model("ModelAssets/Barrel.obj", path);
    barrel->SetScale(transform.scale);
    
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
    
    // If the target goes under the map... fix it.
    if(transform.position.y > -1.2f) transform.position.y = -1.2f;

    // The maximum distance a target is allowed to be from the player..
    constexpr float maxDistance = 65;
    
    // Prevent the targets from moving if they move too far away from the player
    far = distance(rPlayerPos, transform.position) > maxDistance;

    // Speed up if far away
    moveSpeed = far? 1.5f : .5f;
    
    // If the target gets too far from the player move to the player (if it's moveable) otherwise teleport near the player.
    if(far && moveable) moveDir = normalize(rPlayerPos - transform.position);
    else if(far && !moveable) Relocate();

    // Set position/rotation
    barrel->SetRotation(transform.rotation);
    barrel->SetPosition(transform.position);
}

void Target::Relocate()
{
    // Set the position of the target to a random position around the player
    const glm::vec3 randomOffset = glm::ballRand(relocateRadius);
    transform.position = rPlayerPos + randomOffset;
}

void Target::Move()
{
    // Doesn't need deltaTime since it's run in FixedUpdate
    constexpr float rotSpeed = .001f;
    
    // Slowly rotate the object.
    transform.rotation = mix(transform.rotation, transform.rotation + moveDir, rotSpeed);
    
    if(!moveable) return;

    transform.position += moveDir * moveSpeed;
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
