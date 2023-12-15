// @file: SkeletonController.cpp
//
// @brief: Skeletons will move towards the player then stop short and attack
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#pragma once
#ifndef _SKELETON_CONTROLLER_
#define _SKELETON_CONTROLLER_

#include "GameCore.h"
#include "TextureAsset.h"
#include "Sprite.h"
#include "EnemyHealthModule.h"

class SkeletonController : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(SkeletonController, Component);

	//Holds onto the player Entity for future reference
	Entity* _player;

	//Holds the TextureAssets for the different directions
	TextureAsset* _forward = nullptr;
	TextureAsset* _backward = nullptr;
	TextureAsset* _left = nullptr;
	TextureAsset* _right = nullptr;

	//Holds onto the Entities Sprite for future reference
	Sprite* _sprite = nullptr;

	//Holds onto the enemy health module for future reference
	EnemyHealthModule* _healthModule = nullptr;

	//Holds onto the collider for future reference
	BoxCollider* _collider = nullptr;

	//Used for dealing with collisions with walls and other enemies
	Vec2 _directionOnCollision = Vec2(0, 0);
	bool _colliding = false;
	float _collidingTimer = 2;

	//Skeleton movement speed and stop distance
	float _movementSpeed = 50;
	float _stopDistance = 200;

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif