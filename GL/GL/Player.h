#pragma once
#include "Camera.h"
#include <glm.hpp>
#include <utility>
#include <vector>

#include "BoundingBox.h"
#include "Model.h"
#include "Physics.h"

class Player : public Physics
{
public:
	Player(bool running);
	~Player() { delete cam; DeleteMeshPtr(); }

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);

	void Render(const Light& light) { wc.Render(cam, light); }
	void Debug() { wc.Debug(); }

	Camera* GetCamera() const { if(!cam) print("unable to get Cam") return cam; }

	glm::vec3 GetPosition() const { return position; }

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

		void Render(Camera* cam, const Light& light) const;
		void Debug() const { Raycast::DebugDrawRay(ray); }
		
	private:
		void PullTrigger();
		void Shoot();
		bool Reload();
		void ShootTimer(float deltaTime);
		
		Player& rPlayer;
		Model* pistolMesh;

		Raycast::Ray ray;
		
		glm::vec3 shootPos;
		bool canShoot;

		const float shootDelay = .125f;
		float currentShootTime;

		const unsigned short maxAmmo = 120;
		const unsigned short magCapcity = 9;

		unsigned short currentAmmo = maxAmmo;
		unsigned short currentMag = magCapcity;
	};

	WeaponController wc = {this};
};

