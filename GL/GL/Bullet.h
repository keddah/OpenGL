#pragma once
#include "Mesh.h"
#include "Physics.h"

class Bullet : public Physics
{
public:
    Bullet(glm::vec3 spawnPos, glm::vec3 direction, const std::vector<Mesh*>& lvlMeshes);
    ~Bullet() { delete bulletMesh; }
    
    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);
    void Render(Camera* cam, const Light& light) const;

    Mesh* GetMesh() const { return bulletMesh; }

    bool IsDead() const { return dead; }
    
private:
    void MakeSphere();
    void Collisions();
    
    const float lifeSpan = 5; 
    float life = 0;
    bool dead;
    
    glm::vec3 position;
    const float force = 2;

    const std::vector<Mesh*>& levelMeshes;
    Mesh* bulletMesh;
    BoundingBox boundingBox;
};
