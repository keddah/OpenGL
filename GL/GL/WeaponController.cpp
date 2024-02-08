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

    shootPos = rPlayer.position + forwardVec * .05f;
        
    PullTrigger();
    ShootTimer(deltaTime);
}

void Player::WeaponController::Render(Camera* cam, const Light& light) const
{
    if(pistolMesh) pistolMesh->Render(cam, light);
}

void Player::WeaponController::PullTrigger()
{
    if(!rPlayer.controller.LmbDown()) return;

    Shoot();
}

void Player::WeaponController::Shoot()
{
    if(!canShoot) return;

    ray = Raycast::ShootRaycast(shootPos, rPlayer.cam->GetForwardVector(), 9000);

    for(const auto& mesh : rPlayer.meshes)
    {
        const bool hit = Raycast::RayCollision(ray, mesh->GetBoundingBox());

        if(hit)
        {
            std::string floorTex[] = {"Images/gravelBaseColour.jpg", "Images/gravelNormal.jpg"};

            Model* spawnMesh = new Model("ModelAssets/Cube.obj", floorTex);
            spawnMesh->SetScale(.3f,.3f,.3f);
            spawnMesh->SetPosition(ray.hitPosition);
            rPlayer.meshes.push_back(spawnMesh->GetMesh());
            break;
        }
    }
    
    currentMag--;
    if(currentMag <= 0) if(!Reload()) canShoot = false;
}

bool Player::WeaponController::Reload()
{
    currentAmmo -= currentMag + (magCapcity - currentMag);
    currentMag = currentMag + (magCapcity - currentMag);

    return currentAmmo > 0;
}

void Player::WeaponController::ShootTimer(float deltaTime)
{
    if(canShoot) return;

    currentShootTime += deltaTime;
    if(currentShootTime < shootDelay) return;

    currentShootTime = 0;
    canShoot = true;
}
