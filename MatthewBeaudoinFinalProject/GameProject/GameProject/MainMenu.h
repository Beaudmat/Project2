// @file: MainMenu.h
//
// @brief: Checks for the mouse position on screen in the main menu. If the player goes over a button it highlights it,
// if they click on a button it sends the player to the correct scene.
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

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

	//References for the buttons on the main menu
	Sprite* _playButton = nullptr;
	Sprite* _loadButton = nullptr;

	//Scene the playButton will send the player to on click
	unsigned int _playLevel = 0;

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif