/**************************************************************************************************************
* Camera - Code
*
* Creates matrices that give models perspective. The camera is able to move/rotate and is responsible for providing the player with directional
* vectors (up, right, forward)
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#include "Camera.h"
#include <gtx/quaternion.hpp>

Camera::Camera(Controller& roller) : control(roller)
{
    forwardVector = {0,0,-1};

    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    
    aspectRatio = (float)(dm.w / dm.h);
    
    projectionMatrix = glm::perspective(glm::degrees(fov), aspectRatio, nearClip, farClip);
    UpdateViewMatrix();
}

void Camera::Look(glm::vec2 mouseDelta, float deltaTime)
{
    // Handle mouse look
    const float sensitivity_x = 2.0f * deltaTime;
    const float sensitivity_y = 3.0f * deltaTime;

    // Update lookAt based on mouse movement
    forwardVector = rotate(glm::mat4(1.0f), mouseDelta.x * sensitivity_x, glm::vec3(0, 1, 0)) * glm::vec4(forwardVector, 0.0f);
    rightVector = normalize(glm::cross(forwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));
    forwardVector = rotate(glm::mat4(1.0f), mouseDelta.y * sensitivity_y, rightVector) * glm::vec4(forwardVector, 0.0f);

    // Normalize lookAt vector
    forwardVector = normalize(forwardVector);

    // Use the updated forward vector to get the right vector
    rightVector = normalize(glm::cross(forwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));

    // Calculate the up vector using the cross product of forward and right
    upVector = normalize(glm::cross(rightVector, forwardVector));

    // Update lookAt based on mouse movement
    // const glm::quat rotationX = glm::angleAxis(mouseDelta.x * sensitivity_x, glm::vec3(0, 1, 0));
    // const glm::quat rotationY = glm::angleAxis(mouseDelta.y * sensitivity_y, rightVector);

    // Combine the rotations
    // const glm::quat totalRotation = rotationX * rotationY;
    //
    // pitch = glm::eulerAngles(totalRotation).x;
    // yaw = glm::eulerAngles(totalRotation).y;

    // print("Mouse delta: " << mouseDelta.x << ", " << mouseDelta.y)
    // print("LookAt: " << forwardVector.x << ", " << forwardVector.y << ", " << forwardVector.z)
}
