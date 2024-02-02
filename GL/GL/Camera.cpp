#include "Camera.h"

Camera::Camera(Controller& roller) : control(roller)
{
    position = {0,0,-4};
    lookAt = {0,0,1};

    projectionMatrix = glm::perspective(fov, aspectRatio, nearClip, farClip);
    UpdateViewMatrix();
}

void Camera::Look(glm::vec2 mouseDelta, float deltaTime)
{
    // Handle mouse look
    const float sensitivity_x = 2.5f * deltaTime;
    const float sensitivity_y = 4.25f * deltaTime;
    
    // Update lookAt based on mouse movement
    lookAt = rotate(glm::mat4(1.0f), mouseDelta.x * sensitivity_x, glm::vec3(0, 1, 0)) * glm::vec4(lookAt, 0.0f);
    const glm::vec3 right = normalize(glm::cross(lookAt, glm::vec3(0.0f, 1.0f, 0.0f)));
    lookAt = rotate(glm::mat4(1.0f), mouseDelta.y * sensitivity_y, right) * glm::vec4(lookAt, 0.0f);

    // Normalize lookAt vector
    lookAt = normalize(lookAt);

    print("Mouse delta: " << mouseDelta.x << ", " << mouseDelta.y)
    print("LookAt: " << lookAt.x << ", " << lookAt.y << ", " << lookAt.z)
    
    // const float moveSpeed = 2 * deltaTime;
    // const bool* inputs = control.GetMoveInputs();
    //
    // // Not using else ifs so that multiple inputs can happen at the same time
    // // Forward/Backward
    // if(inputs[0]) position += moveSpeed * lookAt;
    // if(inputs[1]) position -= moveSpeed * lookAt;
    //
    // // Strafing
    // if (inputs[2]) position += glm::normalize(glm::cross(lookAt, glm::vec3(0.0f, 1.0f, 0.0f))) * moveSpeed;  // Strafe left
    // if (inputs[3]) position -= glm::normalize(glm::cross(lookAt, glm::vec3(0.0f, 1.0f, 0.0f))) * moveSpeed;  // Strafe right
    //
    // if(control.JumpBtnDown()) position.y -= moveSpeed;
    // if(control.CrouchBtnDown()) position.y += moveSpeed;
}
