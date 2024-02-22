/**************************************************************************************************************
* Skybox - Header
*
* Contains the class definition for the Skybox class. defines a Mesh pointer and supplies function to get that mesh and render it.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/

#pragma once


#include "Camera.h"
#include "Mesh.h"

class Skybox
{
public:
    Skybox(std::string texturePath);
    ~Skybox() { delete dome; }

    Mesh* GetDomeMesh() const { return dome; }
    void Render(const Camera* cam, const Light& light) const;
    
private:
    Mesh* dome;
    void CreateDome(std::string texturePath);
};
