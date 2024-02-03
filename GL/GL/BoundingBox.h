struct BoundingBox
{
    glm::vec3 min;
    glm::vec3 max;
    glm::vec3 center;

    static bool IsInsideBounds(const glm::vec3& position, const glm::vec3& minBounds, const glm::vec3& maxBounds)
    {
        return
        (
            position.x >= minBounds.x && position.x <= maxBounds.x &&
            position.y >= minBounds.y && position.y <= maxBounds.y &&
            position.z >= minBounds.z && position.z <= maxBounds.z
        );
    }
};

#include <gtx/component_wise.hpp>

struct Raycast
{
    struct Ray
    {
        glm::vec3 start;
        glm::vec3 end;
    } ray;

    static Ray ShootRaycast(const glm::vec3& rayStart, const glm::vec3& rayDirection, const float rayDistance) 
    {
        return {rayStart + rayDirection * rayDistance};
    }

    static bool RayCollision(const glm::vec3& rayStart, const glm::vec3& rayDirection, const float rayDistance, const BoundingBox& bb) 
    {
        const Ray ray = ShootRaycast(rayStart, rayDirection, rayDistance);

        for (int i = 0; i < 3; ++i)
        {
            const float invDirection = 1.0f / rayDirection[i];
            const float tMin = (bb.min[i] - ray.start[i]) * invDirection;
            const float tMax = (bb.max[i] - ray.start[i]) * invDirection;

            const float tEnter = glm::min(tMin, tMax);
            const float tExit = glm::max(tMin, tMax);

            if (tEnter > tExit || tExit < 0)
                return false;
        }

        return true;
    }
};
