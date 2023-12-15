#pragma once
#ifndef _PAUSE_MENU_
#define _PAUSE_MENU_

#include "Gamecore.h"
#include "Sprite.h"

class PauseMenu : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(PauseMenu, Component);

    SDL_Color _highlightColor = { 55, 142, 153, 255 };

    Sprite* _continueButton = nullptr;
    Sprite* _saveButton = nullptr;
    Sprite* _quitButton = nullptr;

    unsigned int _quitScene = 0;

    unsigned int _returnScene = 0;

public:
    void Initialize() override;

    void Update() override;

    void Load(json::JSON&) override;

    void SetSceneToReturn(unsigned int scene);
};

#endif