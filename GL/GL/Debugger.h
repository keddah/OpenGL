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
    
    void DebugDrawBoundingBox(const BoundingBox& box) const;
    void BoundingBoxDebug(Camera* cam, const BoundingBox& box) const;

    void RayDebug(Camera* cam, const Raycast::Ray& ray) const;

private:
    Transform transform = {{}, {}, {1,1,1}};
    
    Shader shader;
};
