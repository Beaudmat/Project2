// @file: PauseMenu.h
//
// @brief: Pulls the buttons for the pause menu. Tracks the players mouse and if it goes over top of the buttons they
// are highlighted. Sends the player to the correct scene if the button is clicked.
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#pragma once
#ifndef _PAUSE_MENU_
#define _PAUSE_MENU_

#include "Gamecore.h"
#include "Sprite.h"

class PauseMenu : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(PauseMenu, Component);

    SDL_Color _highlightColor = { 55, 142, 153, 255 };

    //References to the buttons in the Pause Scene
    Sprite* _continueButton = nullptr;
    Sprite* _saveButton = nullptr;
    Sprite* _quitButton = nullptr;

    //Scene to return to when the quit button is hit
    unsigned int _quitScene = 0;

public:
    void Initialize() override;

    void Update() override;

    void Load(json::JSON&) override;

    void SetSceneToReturn(unsigned int scene);
};

#endif