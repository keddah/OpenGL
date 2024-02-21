#include "Player.h"

Player::WeaponController::WeaponController(Player* player) : rPlayer(*player)
{
    const std::vector<std::string>& texturePaths = {"Images/PistolBaseColour.png", "Images/PistolNormal.png"};
    pistolMesh = new Model("ModelAssets/handgun2.obj", texturePaths);
    
    pistolMesh->SetScale(.01f,.01f,.01f);
    
    pistolMesh->SetCollisionsEnabled(false);
}

void Player::WeaponController::Update(float deltaTime)
{
    //for(int i = 0; i < bullets.size(); i++)
    //{
    //    if(bullets[i]->IsDead())
    //    {
    //        // Delete the bullet instance...
    //        delete bullets[i];

    //        // Then remove the empty space from the vector
    //        bullets.erase(bullets.begin() + i);
    //        continue;
    //    }
    //    
    //    bullets[i]->Update(deltaTime);
    //}
    isADS = rPlayer.controller.RmbDown();
    PullTrigger();
    ShootTimer(deltaTime);

    // Check for reload input. Activate the reload timer once R is pressed (after it elapses the mag is reloaded)
    if(rPlayer.controller.RKeyDown()) reloadOn = true;
    ReloadTimer(deltaTime);
    
    GunPlacement();
}

void Player::WeaponController::FixedUpdate(float deltaTime)
{
    // for(const auto& bullet : bullets) bullet->FixedUpdate(deltaTime);
}

void Player::WeaponController::Render(Camera* camera, const Light& light) const
{
    if(pistolMesh) pistolMesh->Render(camera, light);

    debugger.RayDebug(camera, ray);
    
    // for(const auto& bullet : bullets) bullet->Render(camera, light);
}

void Player::WeaponController::PullTrigger()
{
    if(!rPlayer.controller.LmbDown()) return;

    const glm::vec3 forwardVec = rPlayer.cam->GetForwardVector();
    
    const glm::vec3 shootPos = rPlayer.position + forwardVec * -.025f;
    Shoot(shootPos, forwardVec);
}

void Player::WeaponController::Shoot(glm::vec3 shootPos, glm::vec3 direction)
{
    if(!canShoot) return;

    // Bullet* b = new Bullet(shootPos, direction, rPlayer.meshes);
    // bullets.emplace_back(b);

    if(currentMag == 0)
    {
        // Activate the reload timer once R is pressed (after it elapses the mag is reloaded)
        reloadOn = true;
        
        canShoot = false;
        return;
    }
    
    ray = Raycast::ShootRaycast(shootPos, direction, 600);

    std::string matPath[] = {"Images/defaultTexture.jpg"};
    
    for(const auto& target : targets)
    {
        if(Raycast::RayCollision(ray, target->GetBoundingBox()))
        {
            target->Relocate();
            score++;

            // Give the player ammo after every 100 points.
            if(score % 20 == 0) GiveAmmo();
        }

    }
    
    currentMag--;
    canShoot = false;
}

void Player::WeaponController::ShootTimer(float deltaTime)
{
    if(canShoot) return;

    constexpr float shootDelay = .2f;
    
    currentShootTime += deltaTime;
    if(currentShootTime < shootDelay) return;

    currentShootTime = 0;
    canShoot = true;
}

void Player::WeaponController::Reload()
{
    // Not allowed to reload if the mag is already full
    if (currentMag == magCapcity) return;
       
    // Check if there is enough reserve ammo
    if (currentReserve <= 0)
    {
        currentReserve = 0;
        return;
    }

    // Calculate the number of bullets to reload
    const short bulletsToReload = std::min(magCapcity - currentMag, static_cast<int>(currentReserve));

    // Remove ammo from the reserve
    currentReserve -= bulletsToReload;

    // Add ammo to the mag
    currentMag += bulletsToReload;
}

void Player::WeaponController::ReloadTimer(float deltaTime)
{
    if(!reloadOn) return;

    constexpr float reloadSpeed = .8f;
    
    reloadTimer += deltaTime;
    if(reloadTimer < reloadSpeed) return;

    // Reload once the timer elapses
    Reload();

    // Reset the timer
    reloadTimer = 0;
    reloadOn = false;
}

void Player::WeaponController::GunPlacement()
{
    if (!pistolMesh) return;

    const glm::vec3 forwardVec = rPlayer.cam->GetForwardVector();
    const glm::vec3 rightVec = rPlayer.cam->GetRightVector();

    const glm::vec3 hipOffset = (rightVec * -0.4f) + glm::vec3(0, rPlayer.playerHeight * .125f, 0) + forwardVec * .525f;
    const glm::vec3 adsOffset = glm::vec3(0, rPlayer.playerHeight * .0925f, 0) + forwardVec * .4f;

    const glm::vec3 holdOffset = isADS? adsOffset : hipOffset;
    
    handSocket = mix(handSocket, rPlayer.position + holdOffset, isADS? adsSpeed : 1.0f);
    //handSocket = rPlayer.position + holdOffset;
    pistolMesh->SetPosition(handSocket);

    // Flipping the rotation axis because the model is upside...
    const glm::mat4 lookMatrix = glm::inverse(glm::lookAt(pistolMesh->GetPosition(), pistolMesh->GetPosition() + forwardVec * -1.0f, {0, -1, 0}));
    pistolMesh->LookAtRotation(lookMatrix);
}
