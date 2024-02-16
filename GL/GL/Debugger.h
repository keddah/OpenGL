#pragma once
#include "BoundingBox.h"
#include "Camera.h"
#include "Light.h"
#include "Transform.h"
#include "Rendering/Shader.h"

class Debugger
{
public:
    Debugger();
    
    void DebugDrawBoundingBox(const BoundingBox& box, const glm::vec3& meshPos) const;
    void BoundingBoxDebug(Camera* cam, const glm::vec3& meshPos, const BoundingBox& box) const;

    void RayDebug(Camera* cam, const Raycast::Ray& ray) const;

private:
    Transform transform = {{}, {}, {1,1,1}};
    
    Shader shader {"Rendering/Shaders/VertexShader.glsl", "Rendering/Shaders/FragmentShader.glsl"};
};
