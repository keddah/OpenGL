#pragma once

#include <glew.h>
#include <glm.hpp>

#include <iostream>
#define print(x) { std::cout << x << std::endl; }
#define GetError() { GLenum error = glGetError(); if (error != GL_NO_ERROR) { print("error code: " << error << "\n" << gluErrorString(error)); __debugbreak(); } }
#define glCall(theFunction) { theFunction; GetError(); }

struct BoundingBox
{
    glm::vec3 min;
    glm::vec3 max;
    glm::vec3 center;

    static bool PositionInBounds(const glm::vec3 position, const glm::vec3 minBounds, const glm::vec3 maxBounds, const glm::vec3 threshold = {})
    {
        return
        (
            position.x >= minBounds.x - threshold.x && position.x <= maxBounds.x + threshold.x &&
            position.y >= minBounds.y - threshold.y && position.y <= maxBounds.y + threshold.y &&
            position.z >= minBounds.z - threshold.z && position.z <= maxBounds.z + threshold.z
        );
    }

    static bool PositionInBounds(const glm::vec3 position, const glm::vec3 minBounds, const glm::vec3 maxBounds, glm::vec3 threshold, const float thresholdDynamism)
    {
        threshold *= thresholdDynamism;
        
        return
        (
            position.x >= minBounds.x - threshold.x && position.x <= maxBounds.x + threshold.x &&
            position.y >= minBounds.y - threshold.y && position.y <= maxBounds.y + threshold.y &&
            position.z >= minBounds.z - threshold.z && position.z <= maxBounds.z + threshold.z
        );
    }

    static bool BoundsIntersect(const BoundingBox& box1, const BoundingBox& box2)
    {
        return 
        (
            box1.max.x >= box2.min.x && box1.min.x <= box2.max.x &&
            box1.max.y >= box2.min.y && box1.min.y <= box2.max.y &&
            box1.max.z >= box2.min.z && box1.min.z <= box2.max.z
        );
    }

};

#include <gtc/type_ptr.hpp>
#include <glew.h>

struct Raycast
{
    struct Ray
    {
        glm::vec3 start;
        glm::vec3 end;
        glm::vec3 direction;
        bool hit;
        glm::vec3 hitPosition; 

        static bool IsValid(const Ray& ray) { return glm::length(ray.direction) > 0.0f; }
    } ray;

    static Ray ShootRaycast(const glm::vec3& rayStart, const glm::vec3& rayDirection, const float rayDistance) 
    {
        return { rayStart, rayStart + rayDirection * rayDistance, rayDirection };
    }
    
    static Ray RayCollision(const glm::vec3& rayStart, const glm::vec3& rayDirection, const float rayDistance, const BoundingBox& bb, glm::vec3& hitPosition)
    {
        Ray ray = ShootRaycast(rayStart, rayDirection, rayDistance);

        for (int i = 0; i < 3; ++i)
        {
            // Using the inverse to avoid dividing
            const float invDirection = 1.0f / rayDirection[i];
            const float minIntersect = (bb.min[i] - ray.start[i]) * invDirection;
            const float maxIntersect = (bb.max[i] - ray.start[i]) * invDirection;

            const float entrance = glm::min(minIntersect, maxIntersect);
            const float exit = glm::max(minIntersect, maxIntersect);

            // The entrance value should be smaller than the exit (the ray would be invalid otherwise)...
            // If the exit is less than 0... it never entered (no hit)
            if (entrance > exit || exit < 0)
            {
                ray.hit = false;
                return ray;
            }
               
            // Update hit position when a collision occurs
            hitPosition[i] = ray.start[i] + entrance * rayDirection[i];
        }

        ray.hit = true;
        return ray;
    }

    static bool RayCollision(Ray& ray, const BoundingBox& bb)
    {
        for (int xyz = 0; xyz < 3; ++xyz)
        {
            // Using the inverse to avoid dividing
            const float invDirection = 1.0f / ray.direction[xyz];
            const float minIntersect = (bb.min[xyz] - ray.start[xyz]) * invDirection;
            const float maxIntersect = (bb.max[xyz] - ray.start[xyz]) * invDirection;

            const float entrance = glm::min(minIntersect, maxIntersect);
            const float exit = glm::max(minIntersect, maxIntersect);

            // The entrance value should be smaller than the exit (the ray would be invalid otherwise)...
            // If the exit is less than 0... it never entered (no hit)
            if (entrance > exit || exit < 0)
            {
                // Since the ray parameter is a reference ... this value is usable
                ray.hit = false;
                return false;
            }
               
            // Update hit position when a collision occurs
            ray.hitPosition[xyz] = ray.start[xyz] + entrance * ray.direction[xyz];
        }

        // Since the ray parameter is a reference ... this value is usable
        ray.hit = true;
        return true;
    }

    static void DebugDrawRay(const Ray& ray)
    {
        if (!Ray::IsValid(ray)) return;

        GLuint vao, vbo;
        glCreateVertexArrays(1, &vao);
        glCreateBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        const glm::vec3 vertices[] = { ray.start, ray.end };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        // glColor3f(1.0f, 0.0f, 0.0f);  // Red color for the ray

        glDrawArrays(GL_LINES, 0, 2);

        glDisableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }


};
