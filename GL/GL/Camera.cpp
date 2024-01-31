#include "Camera.h"

Camera::Camera(Controller& roller) : control(roller)
{
    position = {0,0,-4};
    lookAt = {0,0,1};

    projectionMatrix = glm::perspective(fov, aspectRatio, nearClip, farClip);
    UpdateViewMatrix();
}

void Camera::Controls(float deltaTime)
{
    const float moveSpeed = 2 * deltaTime;
    const bool* inputs = control.GetMoveInputs();

    // Not using else ifs so that multiple inputs can happen at the same time
    // Forward/Backward
    if(inputs[0]) position += moveSpeed * lookAt;
    if(inputs[1]) position -= moveSpeed * lookAt;

    // Strafing
    if (inputs[2]) position += glm::normalize(glm::cross(lookAt, glm::vec3(0.0f, 1.0f, 0.0f))) * moveSpeed;  // Strafe left
    if (inputs[3]) position -= glm::normalize(glm::cross(lookAt, glm::vec3(0.0f, 1.0f, 0.0f))) * moveSpeed;  // Strafe right

    if(control.JumpBtnDown()) position.y -= moveSpeed;
    if(control.CrouchBtnDown()) position.y += moveSpeed;
}
