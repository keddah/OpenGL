#pragma once


#include "Camera.h"
#include "Mesh.h"

class Skybox
{
public:
    Skybox(std::string texturePath);
    ~Skybox() { delete dome; }

    Mesh* GetDomeMesh() const { return dome; }
    void Render(Camera* cam, const Light& light);
    
private:
    Mesh* dome;
    void CreateDome(std::string texturePath);
};
