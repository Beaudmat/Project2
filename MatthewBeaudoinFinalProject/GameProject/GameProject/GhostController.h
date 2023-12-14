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

	//Ghost movement speed
	float _movementSpeed = 50;

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif