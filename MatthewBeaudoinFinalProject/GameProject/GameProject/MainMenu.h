#pragma once
#ifndef _MAIN_MENU_
#define _MAIN_MENU_

#include "Gamecore.h"
#include "Sprite.h"

class MainMenu : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(MainMenu, Component);

	SDL_Color _backgroundColor = { 0, 0, 0, 255 };
	SDL_Color _highlightColor = { 55, 142, 153, 255 };

	Sprite* _playButton = nullptr;
	Sprite* _loadButton = nullptr;

	unsigned int _playLevel = 0;

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif