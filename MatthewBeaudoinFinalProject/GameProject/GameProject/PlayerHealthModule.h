// @file: PlayerHealthModule.h
//
// @brief: Tracks the players lives. It will updated the livesUI and sends the player back to the main menu on death
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#pragma once
#ifndef _PLAYER_HEALTH_MODULE_
#define _PLAYER_HEALTH_MODULE_

#include "Gamecore.h"
#include "FontSprite.h"

class PlayerHealthModule : public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(PlayerHealthModule, Component);

    int _lives = 3;

    //holds fontsprite for future reference
    FontSprite* _livesUI = nullptr;

    //Scene to return to when the player runs out of lives
    unsigned int _menuScene = 0;

public:
    void Initialize() override;

    void Update() override;

    void Load(json::JSON&) override;

    void DecreaseLives();

};

#endif