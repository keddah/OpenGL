#include "Player.h"

Player::WeaponController::WeaponController(Player* player) : rPlayer(*player)
{
    string texturePaths [] = {"Images/PistolBaseColour.png", "Images/PistolNormal.png"};
    pistolMesh = new Model("ModelAssets/handgun2.obj", texturePaths);
    
    pistolMesh->SetScale(.01f,.01f,.01f);
    
    pistolMesh->SetCollisionsEnabled(false);
}

void Player::WeaponController::Update(float deltaTime)
{
    for(int i = 0; i < bullets.size(); i++)
    {
        if(bullets[i]->IsDead())
        {
            // Delete the bullet instance...
            delete bullets[i];

            // Then remove the empty space from the vector
            bullets.erase(bullets.begin() + i);
            continue;
        }
        
        bullets[i]->Update(deltaTime);
    }
    isADS = rPlayer.controller.RmbDown();
    PullTrigger();
    ShootTimer(deltaTime);
}

void Player::WeaponController::FixedUpdate(float deltaTime)
{
    if(pistolMesh)
    {
        const glm::vec3 forwardVec = rPlayer.cam->GetForwardVector();
        const glm::vec3 rightVec = rPlayer.cam->GetRightVector();

        const glm::vec3 hipOffset = (rightVec * -0.4f) + glm::vec3(0, rPlayer.playerHeight * .125f, 0) + forwardVec * .525f;
        const glm::vec3 adsOffset = glm::vec3(0, rPlayer.playerHeight * .035f, 0) + forwardVec * .4f;
        const glm::vec3 holdOffset = isADS? adsOffset : hipOffset;
        handSocket = mix(handSocket, rPlayer.position + holdOffset, isADS? adsSpeed : 1.1f);
        // handSocket = rPlayer.position + holdOffset;
        
        // Flipping the rotation axis because the model is upside...
        const glm::mat4 lookMatrix = glm::inverse(glm::lookAt(pistolMesh->GetPosition(), pistolMesh->GetPosition() + forwardVec * -10.0f, {0, -1, 0}));
        
        pistolMesh->LookAtRotation(lookMatrix);
        pistolMesh->SetPosition(handSocket);
    }

    
    for(const auto& bullet : bullets) bullet->FixedUpdate(deltaTime);
}

void Player::WeaponController::Render(Camera* camera, const Light& light) const
{
    if(pistolMesh) pistolMesh->Render(camera, light);

    for(const auto& bullet : bullets) bullet->Render(camera, light);

}

void Player::WeaponController::PullTrigger()
{
    // Check for reload input.
    if(rPlayer.controller.RKeyDown()) Reload();
    
    if(!rPlayer.controller.LmbDown()) return;

    const glm::vec3 forwardVec = rPlayer.cam->GetForwardVector();
    
    const glm::vec3 shootPos = rPlayer.position + forwardVec * -.3f;
    Shoot(shootPos, forwardVec);
}

void Player::WeaponController::Shoot(glm::vec3 shootPos, glm::vec3 direction)
{
    if(!canShoot) return;

    // Bullet* b = new Bullet(shootPos, direction, rPlayer.meshes);
    // bullets.emplace_back(b);

    Raycast::Ray ray = Raycast::ShootRaycast(shootPos, direction, 4000);

    for(const auto& target : targets)
    {
        if(Raycast::RayCollision(ray, target->GetBoundingBox()))
        {
            target->Relocate();
            print("hit")
            print("")
            // Can't shoot though targets
            break;
        }

    }
    
    currentMag--;
    canShoot = false;
    
    if(currentMag <= 0) Reload();
}

void Player::WeaponController::Reload()
{
    // Not allowed to reload if the mag is already full
    if(currentMag == magCapcity) return;
    
    if(currentReserve <= 0)
    {
        currentReserve = 0;
        return;
    }
    
    // The difference of the bullets shot and the mag capacity
    const short bulletsShot = magCapcity - currentMag; 
    
    // Remove the ammo from the reserve
    currentReserve -= bulletsShot;

    // Add it to the mag
    currentMag += bulletsShot;
}

void Player::WeaponController::ShootTimer(float deltaTime)
{
    if(canShoot) return;

    currentShootTime += deltaTime;
    if(currentShootTime < shootDelay) return;

    currentShootTime = 0;
    canShoot = true;
}
