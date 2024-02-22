/**************************************************************************************************************
* Player - Header
*
* The header file for the Player class. Creates a private class for the Weapon controller and Ui class then creates instances of both.
* Outlines the variables and functions that the player object needs in order to draw... and other things.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/

#pragma once
#include "Camera.h"
#include <glm.hpp>
#include <vector>
#include <SDL_ttf.h>

#include "AudioManager.h"
#include "BoundingBox.h"
#include "Bullet.h"
#include "Debugger.h"
#include "ImageRenderer.h"
#include "Model.h"
#include "Physics.h"
#include "Target.h"
#include "TextRenderer.h"

class Player : public Physics
{
public:
	Player(bool& running);
	~Player() { delete cam; }

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);

	// Need to render the UI last
	void Render(const Light& light) const { wc.Render(cam, light); ui.Draw(); }

	Camera* GetCamera() const { if(!cam) print("unable to get Cam") return cam; }
	
	const glm::vec3& GetPosition() const { return position; }

	void SetTargets(const std::vector<Target*>& targets) { wc.SetTargets(targets); } 
	
	void SetLevelMeshes(const std::vector<Mesh*>& newMeshes) { meshes = newMeshes; }
	std::vector<Mesh*> GetLevelMeshes() const { return meshes; }
	
private:
	void Accelerate();
	void Decelerate();
	void Jump();
	void Crouch();
	void Collisions();

	bool accelerating;
	
	glm::vec3 position = { 0, -5, 1.5f};

	Controller controller;
	Camera* cam;

	std::vector<Mesh*> meshes; 
	
	const float playerHeight = 3;
	const float walkSpeed = .3f;
	const float strafeSpeed = walkSpeed * .6f;
	const float sprintSpeed = walkSpeed * 2.15f;
	
	const float walkAccel = .075f;
	const float sprintAccel = walkAccel * .85f;

	// Lateral (side-to-side) acceleration
	const float latAcceleration = walkAccel * .9f;
	
	const float jumpForce = 1.25f;

	class WeaponController
	{
	public:
		WeaponController(Player* player);
		~WeaponController() { delete pistolMesh; DeleteBullets(); targets.clear(); }

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);

		void Render(const Camera* camera, const Light& light) const;

		void SetTargets(const std::vector<Target*>& trgts) { targets = trgts; }

		// UI stuff
		unsigned int GetHits() const { return score; }
		unsigned short GetCurrentMag() const { return currentMag; }
		unsigned short GetCurrentAmmo() const { return currentReserve; }
		
	private:
		void PullTrigger();
		void Shoot(glm::vec3 shootPos, glm::vec3 direction);
		void ShootTimer(float deltaTime);

		void ReloadTimer(float deltaTime);
		void Reload();
		void GiveAmmo() { currentReserve += magCapcity * 3; }
		
		void GunPlacement();

		void DeleteBullets() { for(const auto& bullet : bullets) delete bullet; bullets.clear(); }
		
		Player& rPlayer;
		Model* pistolMesh;

		std::vector<Bullet*> bullets;
		std::vector<Target*> targets;

		Raycast::Ray ray;
		Debugger debugger;

		AudioManager audio;
		
		glm::vec3 handSocket;
		glm::vec3 magSocket;
		bool isADS;
		const float adsSpeed = .6f;
		
		bool canShoot = true;

		float currentShootTime;

		float reloadTimer;
		bool reloadOn, canReload;
		bool reloadSfx;
		const unsigned short maxReserve = 36;
		const unsigned short magCapcity = 9;

		unsigned short currentReserve = maxReserve;
		unsigned short currentMag = magCapcity;

		// The number of targets that have been hit
		unsigned int score = 0;
	};
	WeaponController wc = {this};

	class Ui
	{
	public:
		Ui(Player* player);
		~Ui() { delete ammoRenderer;  delete scoreRenderer; delete crosshair; }
		
		void Draw() const;
		
	private:
		void AmmoCount() const;
		void ScoreCount() const;
		
		Player& rPlayer;
		TextRenderer* ammoRenderer;
		TextRenderer* scoreRenderer;
		ImageRenderer* crosshair;
	};
	
	Ui ui {this};
};

