#pragma once

#include <iostream>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Rendering/BufferArrayManager.h"

class MeshCollider
{
public:
    MeshCollider() = default;

    bool CheckCollision(const glm::vec3& point) const;

protected:
    std::vector<GLuint> indices;
    std::vector<Vertex> vertices;
};

