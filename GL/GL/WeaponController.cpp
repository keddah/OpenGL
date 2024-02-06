#include "Player.h"

Player::WeaponController::WeaponController(Player* player) : rPlayer(*player)
{
    pistolMesh = new Model("ModelAssets/handgun.obj");
    // pistolMesh->SetScale(.01f,.01f,.01f);
    
    pistolMesh->SetCollisionsEnabled(false);
}

void Player::WeaponController::Update(float deltaTime)
{
    const glm::vec3 forwardVec = rPlayer.cam->GetLookAt();
    const glm::vec3 handSocket = (rPlayer.GetPosition() + glm::vec3(0, -rPlayer.playerHeight, 0)) + forwardVec * 1.0f;
    if(pistolMesh)
    {
        // pistolMesh->SetRotation(normalize(forwardVec));
        pistolMesh->SetPosition(handSocket);
    }
}

void Player::WeaponController::Render(Camera* cam) const
{
    if(pistolMesh) pistolMesh->Render(cam);
}
