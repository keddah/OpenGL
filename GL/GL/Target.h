#pragma once

#include <gtc/random.hpp>
#include <glm.hpp>
#include <gtx/vector_angle.hpp> 

#include "Model.h"
#include "Physics.h"
#include "Transform.h"


class Target : public  Physics
{
public:
    Target(bool moving, const glm::vec3& playerPos);
    ~Target() { delete barrel; otherMeshes.clear(); }
    
    void Render(Camera* cam, const Light& light) const { if(barrel) barrel->Render(cam, light); }
    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);

    // Moves the object to a random location within a range
    void Relocate();

    bool IsMoveable() const { return moveable; }
    void SetMoveable(const bool move) { moveable = move; }

    void SetMeshes(const std::vector<Mesh*>& meshes) { otherMeshes = meshes; }
    BoundingBox GetBoundingBox() const { return barrel->GetMesh()->GetBoundingBox(); }
    
private:
    void Move();
    void Timers(float deltaTime);
    void Collisions();
    void Decelerate();

    // Generate a random direction
    void RandomDirection() { if(!far) moveDir = linearRand(glm::vec3(-1.0f), glm::vec3(1.0f)); }

    glm::vec3 minVelocity;
    bool moveable, far;
    bool changeDir;
    const float relocateRadius = 40;

    const glm::vec3& rPlayerPos;
    float teleportTimer;
    bool teleport;
    
    // The timer used to change direction whenever it elapses
    float directionTimer;
    float moveSpeed;
    glm::vec3 moveDir;
    unsigned short dirChanges = 0;
    
    Transform transform = {{}, {}, {3,3,3}};
    Model* barrel;

    std::vector<Mesh*> otherMeshes;
};

