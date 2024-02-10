#include "Target.h"

Target::Target(const bool moving) : moveable(moving)
{
    std::string path[] = {"Images/Barrel_d", "Images/Barrel_n" };
    barrel = new Model("ModelAssets/Barrel.obj", path);
}

void Target::Update(float deltaTime)
{
    MoveTimer(deltaTime);
}

void Target::FixedUpdate(float deltaTime)
{
    Move();
}

void Target::Move()
{
    if(!moveable) return;

    transform.position += moveDir * moveSpeed;
    barrel->SetPosition(transform.position);
}

void Target::MoveTimer(float deltaTime)
{
    if(changeDir) return;

    // Speed up the direction changes depending on how many direction changes there are
    deltaTime += (static_cast<float>(dirChanges) * .05f);

    // So that the object doesn't eventually end up changing direction every frame (it'll barely move and jitter a lot).
    const float minimumDirTime = dirDuration - .65f;
    
    if(deltaTime > minimumDirTime) deltaTime = minimumDirTime; 

    // The actual timer
    directionTimer += deltaTime;
    if(directionTimer < dirDuration) return;
    
    RandomDirection();
    dirChanges++;
    changeDir = true;
}
