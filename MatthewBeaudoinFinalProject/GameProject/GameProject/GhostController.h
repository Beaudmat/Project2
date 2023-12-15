// @file: GhostController.h
//
// @brief: Ghosts will chase after the player and destroy themselves on impact damaging the player
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#pragma once
#ifndef _GHOST_CONTROLLER_
#define _GHOST_CONTROLLER_

#include "GameCore.h"
#include "TextureAsset.h"
#include "Sprite.h"
#include "EnemyHealthModule.h"

class GhostController : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(GhostController, Component);

	//Used for referencing the player Entity
	Entity* _player;

	//Holds the TextureAssets for the different directions
	TextureAsset* _forward = nullptr;
	TextureAsset* _backward = nullptr;
	TextureAsset* _left = nullptr;
	TextureAsset* _right = nullptr;

	//Used for referencing the Entities Sprite
	Sprite* _sprite = nullptr;

	//Holds onto the enemy health module for future reference
	EnemyHealthModule* _healthModule = nullptr;

	//Holds onto the collider for future reference
	BoxCollider* _collider = nullptr;

	//Used for dealing with collisions with walls and other enemies
	Vec2 _directionOnCollision = Vec2(0, 0);
	bool _colliding = false;
	float _collidingTimer = 2;

	//Ghost movement speed
	float _movementSpeed = 50;

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif