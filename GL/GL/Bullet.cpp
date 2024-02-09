#include "Bullet.h"
#include <gtx/quaternion.hpp>


Bullet::Bullet(const glm::vec3 spawnPos, const glm::vec3 direction)
{
    MakeSphere();
    position = spawnPos;
    gravMultiplier = .05f;
    AddForce(direction, force);
}

void Bullet::Update(float deltaTime)
{
    life += deltaTime;
    if(life >= lifeSpan) dead = true;
    
    if(mesh) mesh->SetPosition(position);
}

void Bullet::FixedUpdate(float deltaTime)
{
    ApplyGravity(deltaTime);
    
    position += velocity;
}

void Bullet::Render(Camera* cam, const Light& light) const
{
    if(mesh) mesh->Render(cam, light);
}

void Bullet::MakeSphere()
{
    const float radius = 1;
    constexpr int stacks = 20;
    constexpr int sectors = 20;
    
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    for (int i = 0; i <= stacks; ++i)
    {
        float lat0 = M_PI * (-0.5 + static_cast<float>(i) / stacks);
        float z0 = sin(lat0) * radius;
        float zr0 = cos(lat0) * radius;

        for (int j = 0; j <= sectors; ++j)
        {
            float lng = 2 * M_PI * static_cast<float>(j) / sectors;
            float x = cos(lng) * radius;
            float y = sin(lng) * radius;

            float u = static_cast<float>(j) / sectors;
            float v = 1.0f - static_cast<float>(i) / stacks;

            // Vertex coordinates
            vertices.push_back(x * zr0);  // X coordinate
            vertices.push_back(y * zr0);  // Y coordinate
            vertices.push_back(z0);       // Z coordinate

            // Normal vector
            vertices.push_back(x);  // X normal
            vertices.push_back(y);  // Y normal
            vertices.push_back(z0); // Z normal

            // UV coordinates
            vertices.push_back(u); // U coordinate
            vertices.push_back(v); // V coordinate
        }
    }

    for (int i = 0; i < stacks; ++i)
    {
        for (int j = 0; j <= sectors; ++j)
        {
            int nextRow = i + 1;
            int nextColumn = (j + 1) % (sectors + 1);

            indices.push_back(i * (sectors + 1) + j);
            indices.push_back(nextRow * (sectors + 1) + j);
            indices.push_back(i * (sectors + 1) + nextColumn);

            indices.push_back(i * (sectors + 1) + nextColumn);
            indices.push_back(nextRow * (sectors + 1) + j);
            indices.push_back(nextRow * (sectors + 1) + nextColumn);
        }
    }

    const std::string images[] = {"Images/defaultTexture.jpg"};
    mesh = new Mesh(vertices, indices, images);
    mesh->SetScale(.1f);
}