#include "MeshCollider.h"

bool MeshCollider::CheckCollision(const glm::vec3& point) const
{
    for (size_t i = 0; i < vertices.size(); i += Vertex::GetCount()) {
        const glm::vec3& v0 = vertices[i].GetPositionVec();
        const glm::vec3& v1 = vertices[i + 1].GetPositionVec();
        const glm::vec3& v2 = vertices[i + 2].GetPositionVec();

        // Calculate the normal of the triangle
        glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

        // Check if the point is on the same side of the plane as the triangle
        float distance = glm::dot(normal, v0);

        // If the point is on the same side of the plane as the triangle, skip to the next triangle
        if (glm::dot(normal, point) - distance > 0) continue;

        // Calculate barycentric coordinates
        glm::vec3 edge0 = v1 - v0;
        glm::vec3 edge1 = v2 - v1;
        glm::vec3 edge2 = v0 - v2;

        glm::vec3 c0 = glm::cross(edge0, point - v0);
        glm::vec3 c1 = glm::cross(edge1, point - v1);
        glm::vec3 c2 = glm::cross(edge2, point - v2);

        // Check if the point is inside the triangle using barycentric coordinates
        if (glm::dot(normal, c0) >= 0 && glm::dot(normal, c1) >= 0 && glm::dot(normal, c2) >= 0)
        {
            return true;  // Point is inside the triangle
        }
    }

    return false;  // Point is outside all triangles
}