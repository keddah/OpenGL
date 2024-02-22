/**************************************************************************************************************
* Debugger - Header
*
* The header file for the debugger class. Responsible for providing get functions that draw raycasts and bounding boxes.
* Also creates a shader instance.
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#pragma once

#include "BoundingBox.h"
#include "Camera.h"
#include "Light.h"
#include "Transform.h"
#include "Rendering/Shader.h"

class Debugger
{
public:
    Debugger() { shader.Init(); }
    
    void DebugDrawBoundingBox(const BoundingBox& box, const glm::vec3& meshPos) const;
    void BoundingBoxDebug(const Camera* cam, const glm::vec3& meshPos, const BoundingBox& box) const;

    void RayDebug(const Camera* cam, const Raycast::Ray& ray) const;

private:
    Transform transform = {{}, {}, {1,1,1}};
    
    Shader shader {"Rendering/Shaders/VertexShader.glsl", "Rendering/Shaders/FragmentShader.glsl"};
};
