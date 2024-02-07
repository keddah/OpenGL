#include "Player.h"

Player::WeaponController::WeaponController(Player* player) : rPlayer(*player)
{
    pistolMesh = new Model("ModelAssets/handgun.obj");
    
    pistolMesh->SetCollisionsEnabled(false);
}

void Player::WeaponController::Update(float deltaTime)
{
    const glm::vec3 forwardVec = rPlayer.cam->GetForwardVector();
    //const glm::vec3 holdOffset = (forwardVec * 2.0f) + (rPlayer.cam->GetRightVector() * -2.0f) + rPlayer.playerHeight * .5f;
    const glm::vec3 holdOffset = (forwardVec * 2.0f) + (rPlayer.cam->GetRightVector() * -2.0f) + rPlayer.playerHeight * .5f;
    //const glm::vec3 holdOffset = (forwardVec * 2.0f) + rPlayer.playerHeight * .5f;

    const glm::vec3 handSocket = rPlayer.position + holdOffset + forwardVec * 3.0f;                          // Flipping the rotation axis because the model is upside...
    const glm::mat4 lookMatrix = glm::inverse(glm::lookAt(pistolMesh->GetPosition(), pistolMesh->GetPosition() + forwardVec * -100.0f, {0,-1,0}));

    if(pistolMesh)
    {
        pistolMesh->LookAtRotation(lookMatrix);
        pistolMesh->SetPosition(handSocket);
    }
}

void Player::WeaponController::Render(Camera* cam, Light light) const
{
    if(pistolMesh) pistolMesh->Render(cam, light);
}
