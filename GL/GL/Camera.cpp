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

    // Not using else ifs so that multiple inputs can happen at the same time
    if(inputs[0]) position.z += moveSpeed;
    if(inputs[1]) position.z -= moveSpeed;
    if(inputs[2]) position.x -= moveSpeed;
    if(inputs[3]) position.x += moveSpeed;

    if(control.JumpBtnDown()) position.y -= moveSpeed;
    if(control.CrouchBtnDown()) position.y += moveSpeed;
}
