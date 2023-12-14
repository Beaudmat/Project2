// @file:WitchController.h
//
// @brief: Witches will move towards the player however will stop far away and shoot projectiles at them
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#pragma once
#ifndef _WITCH_CONTROLLER_
#define _WITCH_CONTROLLER_

#include "GameCore.h"
#include "TextureAsset.h"
#include "Sprite.h"

class WitchController : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(WitchController, Component);

	//Used for referencing the player in the future
	Entity* _player;

	//Holds the TextureAssets for the different directions
	TextureAsset* _forward = nullptr;
	TextureAsset* _backward = nullptr;
	TextureAsset* _left = nullptr;
	TextureAsset* _right = nullptr;

	//Used for reference the Entities Sprite in the future
	Sprite* _sprite = nullptr;

	//Holds the TextureAssets for the Bullet
	TextureAsset* _bullet = nullptr;

	//Time between bullet shots
	float _timeBetweenShotsMax = 5;
	float _timeBetweenShots = 1;

	//Bullet speed
	float _shotSpeed = 100;

	//Witch move speed and stop distance
	float _movementSpeed = 50;
	float _stopDistance = 200;

public:

	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif