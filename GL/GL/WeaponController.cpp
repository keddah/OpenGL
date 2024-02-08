#include "Player.h"

Player::WeaponController::WeaponController(Player* player) : rPlayer(*player)
{
    string texturePaths [] = {"Images/PistolBaseColour.png", "Images/PistolNormal.png"};
    pistolMesh = new Model("ModelAssets/handgun2.obj", texturePaths);
    // pistolMesh->CreateMaterial();
    
    pistolMesh->SetScale(.01f,.01f,.01f);
    
    pistolMesh->SetCollisionsEnabled(false);
}

void Player::WeaponController::Update(float deltaTime)
{
    const glm::vec3 forwardVec = rPlayer.cam->GetForwardVector();
    const glm::vec3 rightVec = rPlayer.cam->GetRightVector();

    const glm::vec3 holdOffset = (rightVec * -0.4f) + glm::vec3(0, rPlayer.playerHeight * .125f, 0) + forwardVec * -2.325f;
    const glm::vec3 handSocket = rPlayer.position + holdOffset + forwardVec * 3.0f;
                                                                                                                                        // Flipping the rotation axis because the model is upside...
    const glm::mat4 lookMatrix = glm::inverse(glm::lookAt(pistolMesh->GetPosition(), pistolMesh->GetPosition() + forwardVec * -10.0f, {0, -1, 0}));

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
