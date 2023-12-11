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
	float _levelTimer = 30;
	float _levelTimerMax = 30;

	FontSprite* _levelTimerText = nullptr;

	SDL_Color _textCurrentColor = { 255, 255, 255, 255 };

	unsigned int _sceneOnTimeout = 0;
};

#endif