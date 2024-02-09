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
    for(int i = 0; i < bullets.size(); i++)
    {
        if(bullets[i]->IsDead())
        {
            rPlayer.RemoveLevelMesh(bullets[i]->GetMesh());

            // Delete after getting the mesh so that the mesh isn't deleted
            delete bullets[i];
            
            bullets.erase(bullets.begin() + i);
            continue;
        }
        
        bullets[i]->Update(deltaTime);
    }

    PullTrigger();
    ShootTimer(deltaTime);
}

void Player::WeaponController::FixedUpdate(float deltaTime)
{
    for(const auto& bullet : bullets) bullet->FixedUpdate(deltaTime);
}

void Player::WeaponController::Render(Camera* cam, const Light& light) const
{
    if(pistolMesh) pistolMesh->Render(cam, light);
}

void Player::WeaponController::PullTrigger()
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
    
    if(!rPlayer.controller.LmbDown()) return;

    const glm::vec3 shootPos = rPlayer.position + forwardVec * -.3f;
    Shoot(shootPos, forwardVec);
}

void Player::WeaponController::Shoot(glm::vec3 shootPos, glm::vec3 direction)
{
    if(!canShoot) return;

    Bullet* b = new Bullet(shootPos, direction, rPlayer.meshes);
    rPlayer.AddLevelMesh(b->GetMesh());
    bullets.emplace_back(b);
    
    currentMag--;
    canShoot = false;
    
    if(currentMag <= 0) Reload();
}

void Player::WeaponController::Reload()
{
    // Remove the ammo from the reserve
    currentAmmo -= currentMag + (magCapcity - currentMag);

    // Add it to the mag
    currentMag = currentMag + (magCapcity - currentMag);
}

void Player::WeaponController::ShootTimer(float deltaTime)
{
    if(canShoot) return;

    currentShootTime += deltaTime;
    if(currentShootTime < shootDelay) return;

    currentShootTime = 0;
    canShoot = true;
}
