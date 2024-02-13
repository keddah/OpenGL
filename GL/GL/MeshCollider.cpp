#include "MeshCollider.h"

// bool MeshCollider::CheckCollision(const glm::vec3& point) const
// {
//     for (size_t i = 0; i < indices.size(); i += 3)
//     {
//         const Vertex& v0 = vertices[indices[i]];
//         const Vertex& v1 = vertices[indices[i + 1]];
//         const Vertex& v2 = vertices[indices[i + 2]];
//
//         glm::vec3 e1 = v1.GetPositionVec() - v0.GetPositionVec();
//         glm::vec3 e2 = v2.GetPositionVec() - v0.GetPositionVec();
//         glm::vec3 h = glm::cross(rayDirection, e2);
//         float a = glm::dot(e1, h);
//
//         if (a > -0.00001f && a < 0.00001f)
//             continue;
//
//         float f = 1.0f / a;
//         glm::vec3 s = rayOrigin - v0.GetPositionVec();
//         float u = f * glm::dot(s, h);
//
//         if (u < 0.0f || u > 1.0f)
//             continue;
//
//         glm::vec3 q = glm::cross(s, e1);
//         float v = f * glm::dot(rayDirection, q);
//
//         if (v < 0.0f || u + v > 1.0f)
//             continue;
//
//         float t = f * glm::dot(e2, q);
//
//         if (t > 0.00001f)
//         {
//             // Collision detected
//             return true;
//         }
//     }
//
//     // No collision
//     return false;
//
//
//     
//     for (size_t i = 0; i < vertices.size(); i += Vertex::GetCount()) {
//         const glm::vec3& v0 = vertices[i].GetPositionVec();
//         const glm::vec3& v1 = vertices[i + 1].GetPositionVec();
//         const glm::vec3& v2 = vertices[i + 2].GetPositionVec();
//
//         // Calculate the normal of the triangle
//         glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
//
//         // Check if the point is on the same side of the plane as the triangle
//         float distance = glm::dot(normal, v0);
//         if (glm::dot(normal, point) - distance > 0) {
//             continue;
//         }
//
//         // Check if the point is inside the triangle using barycentric coordinates
//         glm::vec3 edge0 = v1 - v0;
//         glm::vec3 edge1 = v2 - v1;
//         glm::vec3 edge2 = v0 - v2;
//
//         glm::vec3 c0 = glm::cross(edge0, point - v0);
//         glm::vec3 c1 = glm::cross(edge1, point - v1);
//         glm::vec3 c2 = glm::cross(edge2, point - v2);
//
//         if (glm::dot(normal, c0) >= 0 && glm::dot(normal, c1) >= 0 && glm::dot(normal, c2) >= 0) {
//             return true;  // Point is inside the triangle
//         }
//     }
//
//     return false;
// }


bool MeshCollider::CheckCollision(const glm::vec3& point) const
{
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        const Vertex& v0 = vertices[indices[i]];
        const Vertex& v1 = vertices[indices[i + 1]];
        const Vertex& v2 = vertices[indices[i + 2]];

        // Check if the point is inside the triangle
        if (IsPointInTriangle(point, v0.GetPositionVec(), v1.GetPositionVec(), v2.GetPositionVec()))
        {
            return true;  // Collision detected
        }
    }

    // No collision
    return false;
}

bool MeshCollider::IsPointInTriangle(const glm::vec3& p, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) const
{
    // Barycentric coordinates
    float u = glm::dot((v1 - v0), (p - v0)) / glm::dot((v1 - v0), (v1 - v0));
    float v = glm::dot((v2 - v0), (p - v0)) / glm::dot((v2 - v0), (v2 - v0));

    // Check if the point is inside the triangle
    return (u >= 0.0f) && (v >= 0.0f) && (u + v <= 1.0f);
}
