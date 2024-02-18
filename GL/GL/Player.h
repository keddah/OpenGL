#pragma once
#include "Camera.h"
#include <glm.hpp>
#include <utility>
#include <vector>

#include "BoundingBox.h"
#include "Bullet.h"
#include "Debugger.h"
#include "Model.h"
#include "Physics.h"
#include "Target.h"
#include "Terrain.h"
#include "TextRenderer.h"

class Player : public Physics
{
public:
	Player(bool& running);
	~Player() { delete cam; DeleteMeshPtr(); }

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);

	void Render(const Light& light) const
	{ wc.Render(cam, light); ui.Draw(); }

	Camera* GetCamera() const { if(!cam) print("unable to get Cam") return cam; }
	
	const glm::vec3& GetPosition() const { return position; }

	void SetTargets(const std::vector<Target*>& trgts) { wc.SetTargets(trgts); } 
	
	void SetLevelMeshes(const std::vector<Mesh*>& newMeshes) { meshes = newMeshes; }
	std::vector<Mesh*> GetLevelMeshes() const { return meshes; }
	
private:
	void Accelerate(float deltaTime);
	void Decelerate(float deltaTime);
	void Jump();
	void Crouch();
	void Collisions();

	void DeleteMeshPtr() const { for (const auto& mesh : meshes) delete mesh; }

	bool accelerating;
	
	glm::vec3 position = { 0, -5, 1.5f};

	Controller controller;
	Camera* cam;

	std::vector<Mesh*> meshes; 
	
	const float playerHeight = 3;
	const float walkSpeed = .3f;
	const float strafeSpeed = walkSpeed * .6f;
	const float sprintSpeed = walkSpeed * 2.15f;
	
	const float jumpForce = 1.25f;

	class WeaponController
	{
	public:
		WeaponController(Player* player);
		~WeaponController() { delete pistolMesh; }

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);

		void Render(Camera* camera, const Light& light) const;

		void SetTargets(const std::vector<Target*>& trgts) { targets = trgts; }

		// UI stuff
		unsigned int GetHits() const { return targetsHit; }
		unsigned short GetCurrentMag() const { return currentMag; }
		unsigned short GetCurrentAmmo() const { return currentReserve; }
		
	private:
		void PullTrigger();
		void Shoot(glm::vec3 shootPos, glm::vec3 direction);
		void Reload();
		void ShootTimer(float deltaTime);
		
		void GunPlacement();

		Player& rPlayer;
		Model* pistolMesh;

		std::vector<Bullet*> bullets;
		std::vector<Target*> targets;

		Raycast::Ray ray;
		Debugger debugger;
		
		glm::vec3 handSocket;
		glm::vec3 magSocket;
		bool isADS;
		const float adsSpeed = .6f;
		
		bool canShoot = true;

		const float shootDelay = .2f;
		float currentShootTime;

		const unsigned short maxReserve = 120;
		const unsigned short magCapcity = 9;

		unsigned short currentReserve = maxReserve;
		unsigned short currentMag = magCapcity;

		// The number of targets that have been hit
		unsigned int targetsHit = 0;
	};
	WeaponController wc = {this};

#include <SDL_ttf.h>
	class Ui
	{
	public:
		Ui(Player* player);
		void Draw() const;
		void Update(float deltaTime);
		
	private:
		void AmmoCount() const;
		void ScoreCount() const;
		
		Player& rPlayer;
		TextRenderer* ammoRenderer;
		TextRenderer* scoreRenderer;

		glm::vec2 screenSize;
		
	};
	
	Ui ui {this};
};

