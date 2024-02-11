#pragma once

#include <glew.h>

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
            const float invDirection = 1.0f / rayDirection[i];
            const float tMin = (bb.min[i] - ray.start[i]) * invDirection;
            const float tMax = (bb.max[i] - ray.start[i]) * invDirection;

            const float tEnter = glm::min(tMin, tMax);
            const float tExit = glm::max(tMin, tMax);

            if (tEnter > tExit || tExit < 0)
            {
                ray.hit = false;
                return ray;
            }
               
            // Update hit position when a collision occurs
            hitPosition[i] = ray.start[i] + tEnter * rayDirection[i];
        }

        ray.hit = true;
        return ray;
    }

    static bool RayCollision(Ray& ray, const BoundingBox& bb)
    {
        for (int i = 0; i < 3; ++i)
        {
            const float invDirection = 1.0f / ray.direction[i];
            const float tMin = (bb.min[i] - ray.start[i]) * invDirection;
            const float tMax = (bb.max[i] - ray.start[i]) * invDirection;

            const float tEnter = glm::min(tMin, tMax);
            const float tExit = glm::max(tMin, tMax);

            if (tEnter > tExit || tExit < 0)
            {
                // Since the ray parameter is a reference ... this value is usable
                ray.hit = false;
                return false;
            }
               
            // Update hit position when a collision occurs
            ray.hitPosition[i] = ray.start[i] + tEnter * ray.direction[i];
        }

        // Since the ray parameter is a reference ... this value is usable
        ray.hit = true;
        return true;
    }

    static void DebugDrawRay(const Ray& ray)
    {
        if(!Ray::IsValid(ray)) return;
        glUseProgram(0);

        glColor3f(1.0f, 0.0f, 0.0f);  // Red color for the ray

        glBegin(GL_LINES);
        glVertex3fv(glm::value_ptr(ray.start));
        glVertex3fv(glm::value_ptr(ray.end));
        glEnd();
    }
};
