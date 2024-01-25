#include "Camera.h"

Camera::Camera(Controller& roller) : control(roller)
{
    position = {0,0,-4};
    lookAt = {0,0,1};

    projectionMatrix = glm::perspective(fov, aspectRatio, nearClip, farClip);
    UpdateViewMatrix();
}

void Camera::Move()
{
    constexpr float moveSpeed = .001f;
    const bool* inputs = control.GetMoveInputs();
    if(inputs[0]) position.z += moveSpeed;
    else if(inputs[1]) position.z -= moveSpeed;
    else if(inputs[2]) position.x -= moveSpeed;
    else if(inputs[3]) position.x += moveSpeed;
}
