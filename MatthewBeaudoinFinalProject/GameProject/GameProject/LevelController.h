// @file: LevelController.h
//
// @brief: Checks if the player has hit the pause button and transfers them to the pause menu
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#pragma once
#ifndef _LEVEL_CONTROLLER_
#define _LEVEL_CONTROLLER_

#include "GameCore.h"

class LevelController : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(LevelController, Component);

	//Scene the player is sent to when they hit ~
	unsigned int _pauseScene = 0;

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif