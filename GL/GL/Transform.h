/**************************************************************************************************************
* Transform - Header
*
* Contains a struct that's used to keep track of an object's position, rotation and scale (its transform).
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/

#pragma once

struct Transform
{
    glm::vec3 position = {};        
    glm::vec3 rotation = {};        
    glm::vec3 scale = {1,1,1};        
};