/**************************************************************************************************************
* Bounding Box - Header
*
* Contains the struct for Bounding boxes. Also contains the struct for Raycasts. They are grouped together because raycast are very quite dependent on
* boundind boxes.
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


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

    static bool PositionInBounds(const glm::vec3 position, const BoundingBox& box, const glm::vec3 threshold = {})
    {
        return
        (
            position.x >= box.min.x - threshold.x && position.x <= box.max.x + threshold.x &&
            position.y >= box.min.y - threshold.y && position.y <= box.max.y + threshold.y &&
            position.z >= box.min.z - threshold.z && position.z <= box.max.z + threshold.z
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
        return { rayStart, rayStart + normalize(rayDirection) * rayDistance, normalize(rayDirection) };
    }
    
    static Ray RayCollision(const glm::vec3& rayStart, const glm::vec3& rayDirection, const float rayDistance, const BoundingBox& bb, glm::vec3& hitPosition)
    {
        Ray ray = ShootRaycast(rayStart, normalize(rayDirection), rayDistance);

        float tmin = -FLT_MAX, tmax = FLT_MAX;

        for (int i = 0; i < 3; ++i) {
            if (ray.direction[i] != 0.0f) {
                const float invDir = 1.0f / ray.direction[i];
                const float t1 = (bb.min[i] - ray.start[i]) * invDir;
                const float t2 = (bb.max[i] - ray.start[i]) * invDir;

                tmin = glm::max(tmin, glm::min(t1, t2));
                tmax = glm::min(tmax, glm::max(t1, t2));
            }
            else if (ray.start[i] < bb.min[i] || ray.start[i] > bb.max[i]) {
                // Ray is parallel to the axis and outside the bounding box
                return ray;
            }
        }

        // Check if the ray misses the box
        if (tmin > tmax || tmax < 0.0f) {
            return ray;
        }

        // Update hit position when a collision occurs
        ray.hitPosition = ray.start + tmin * ray.direction;
        ray.hit = true;

        return ray;
    }

    static bool RayCollision(Ray& ray, const BoundingBox& box)
    {
        float tmin = -FLT_MAX, tmax = FLT_MAX;

        for (int i = 0; i < 3; ++i) {
            if (ray.direction[i] != 0.0f) {
                const float invDir = 1.0f / ray.direction[i];
                const float t1 = (box.min[i] - ray.start[i]) * invDir;
                const float t2 = (box.max[i] - ray.start[i]) * invDir;

                tmin = glm::max(tmin, glm::min(t1, t2));
                tmax = glm::min(tmax, glm::max(t1, t2));
            }
            else if (ray.start[i] < box.min[i] || ray.start[i] > box.max[i]) {
                // Ray is parallel to the axis and outside the bounding box
                return false;
            }
        }

        // Check if the ray misses the box
        if (tmin > tmax || tmax < 0.0f) {
            return false;
        }

        // Update hit position when a collision occurs
        ray.hitPosition = ray.start + tmin * ray.direction;
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
