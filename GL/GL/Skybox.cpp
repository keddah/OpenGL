/**************************************************************************************************************
* Skybox - Code
*
* Creates the vertex positions and indices to produce a sphere and renders it.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/

#include "Skybox.h"

#include <utility>

Skybox::Skybox(std::string texturePath)
{
    CreateDome(std::move(texturePath));
}

void Skybox::Render(const Camera* cam, const Light& light) const
{
    // The skybox needs to move with the camera to make it seem massive
    dome->SetPosition(cam->GetPosition());
    
    dome->Render(cam, light);
}

void Skybox::CreateDome(std::string texturePath)
{
    constexpr int stacks = 20;
    constexpr int sectors = 20;
    
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    for (int i = 0; i <= stacks; ++i)
    {
        const float latitude = M_PI * (-0.5 + static_cast<float>(i) / stacks);
        float z0 = sin(latitude);
        float zr0 = cos(latitude);

        for (int j = 0; j <= sectors; ++j)
        {
            const float longitude = 2 * M_PI * static_cast<float>(j) / sectors;
            float x = cos(longitude);
            float y = sin(longitude);

            float u = -(static_cast<float>(j) / sectors);
            float v = -(1.0f - static_cast<float>(i) / stacks);

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
            const int nextRow = i + 1;
            const int nextColumn = (j + 1) % (sectors + 1);

            indices.push_back(i * (sectors + 1) + j);
            indices.push_back(nextRow * (sectors + 1) + j);
            indices.push_back(i * (sectors + 1) + nextColumn);

            indices.push_back(i * (sectors + 1) + nextColumn);
            indices.push_back(nextRow * (sectors + 1) + j);
            indices.push_back(nextRow * (sectors + 1) + nextColumn);
        }
    }

    const std::vector<std::string>& path= { std::move(texturePath) };
    dome = new Mesh(vertices, indices, path);
    dome->SetScale(400);
    dome->SetRotation(glm::degrees(90.0f),0,0);
    dome->SetCollision(false);

    dome->SetMaterialSpecular(0);
}
