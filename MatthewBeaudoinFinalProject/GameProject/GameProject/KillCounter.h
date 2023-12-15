// @file: KillCounter.h
//
// @brief: Tracks player kills and alters the kill count in the UI
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#pragma once
#ifndef _KILL_COUNTER_
#define _KILL_COUNTER_

#include "GameCore.h"
#include "FontSprite.h"

class KillCounter : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(KillCounter, Component);
    
    int _killCount = 0;

    //Holds onto the fontsprite for future reference
    FontSprite* _killsUI = nullptr;

public:
    void Initialize() override;

    void Update() override;

    void Load(json::JSON&) override;

    void IncreaseKillCount();

    int GetKillCount();
};

#endif