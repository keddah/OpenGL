#include "Camera.h"
#include <gtx/quaternion.hpp>

Camera::Camera(Controller& roller) : control(roller)
{
    position = {0,0,-4};
    forwardVector = {0,0,1};

    projectionMatrix = glm::perspective(fov, aspectRatio, nearClip, farClip);
    UpdateViewMatrix();
}

void Camera::Look(glm::vec2 mouseDelta, float deltaTime)
{
    // Handle mouse look
    const float sensitivity_x = 2.5f * deltaTime;
    const float sensitivity_y = 4.25f * deltaTime;
    
    // Update lookAt based on mouse movement
    forwardVector = rotate(glm::mat4(1.0f), mouseDelta.x * sensitivity_x, glm::vec3(0, 1, 0)) * glm::vec4(forwardVector, 0.0f);
    rightVector = normalize(glm::cross(forwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));
    forwardVector = rotate(glm::mat4(1.0f), mouseDelta.y * sensitivity_y, rightVector) * glm::vec4(forwardVector, 0.0f);

    // Normalize lookAt vector
    forwardVector = normalize(forwardVector);

    // Use the updated forward vector to get the right vector
    rightVector = normalize(glm::cross(forwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));

    glm::vec3 right = GetRightVector();

    print(right.x << ", " << right.y << ", " << right.z);

    // Update lookAt based on mouse movement
    glm::quat rotationX = glm::angleAxis(mouseDelta.x * sensitivity_x, glm::vec3(0, 1, 0));
    glm::quat rotationY = glm::angleAxis(mouseDelta.y * sensitivity_y, GetRightVector());

    // Combine the rotations
    glm::quat totalRotation = rotationX * rotationY;

    pitch = glm::eulerAngles(totalRotation).x;
    yaw = glm::eulerAngles(totalRotation).y;

    // print("Mouse delta: " << mouseDelta.x << ", " << mouseDelta.y)
    //print("LookAt: " << lookAt.x << ", " << lookAt.y << ", " << lookAt.z)
}
