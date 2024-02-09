#pragma once
#include "Mesh.h"
#include "Physics.h"

class Bullet : public Physics
{
public:
    Bullet(glm::vec3 spawnPos, glm::vec3 direction);
    ~Bullet() { delete mesh; }
    
    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);
    void Render(Camera* cam, const Light& light) const;

    Mesh* GetMesh() const { return mesh; }

    bool IsDead() const { return dead; }
    
private:
    void MakeSphere();
    void Collisions();
    
    const float lifeSpan = 5; 
    float life = 0;
    bool dead;
    
    glm::vec3 position;
    const float force = 2;

    Mesh* mesh;
    BoundingBox boundingBox;
};
