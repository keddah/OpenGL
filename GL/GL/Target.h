#pragma once

#include <gtc/random.hpp>

#include "Model.h"
#include "Transform.h"


class Target
{
public:
    Target(bool moving);
    ~Target();
    
    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);

    // Moves the object to a random location within a range
    void Relocate();
    
private:
    void Move();
    void MoveTimer(float deltaTime);

    // Generate a random direction
    void RandomDirection() { moveDir = linearRand(glm::vec3(-1.0f), glm::vec3(1.0f)); }
    
    bool active;
    bool moveable, changeDir;

    // The timer used to change direction whenever it elapses
    float directionTimer;
    float dirDuration = 3;
    float moveSpeed = 1;
    glm::vec3 moveDir;
    unsigned short dirChanges = 0;
    
    Transform transform = {{}, {}, {1,1,1}};
    Model* barrel;
};

