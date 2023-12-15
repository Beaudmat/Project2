// @file: LevelTimer.h
//
// @brief: Tracks the time the player has been in the level. It decreases and when it reaches zero it sends the player
// back to the main menu. It also updates the color of the text based on the time remaining.
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#pragma once
#ifndef _LEVEL_TIMER_
#define _LEVEL_TIMER_

#include "GameCore.h"
#include "FontSprite.h"
#include "UiColorer.h"

class LevelTimer : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(LevelTimer, Component);

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;

private:

	//Timer for how long the player has been in the level
	float _levelTimer = 30;
	float _levelTimerMax = 30;

	//Reference to the timer UI font
	FontSprite* _levelTimerText = nullptr;

	//Orginal font color for the timer UI
	SDL_Color _textCurrentColor = { 255, 255, 255, 255 };

	//Scene to go to when the timer runs out
	unsigned int _sceneOnTimeout = 0;
};

#endif