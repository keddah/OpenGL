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