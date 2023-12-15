// @file: PauseInformationHolder.h
//
// @brief: Singleton design. Allows levels to pass information about themselves to the PauseMenu so the PauseMenu knows
// what scene to return too when the player clicks continue
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#pragma once
#ifndef _PAUSE_INFORMATION_HOLDER_
#define _PAUSE_INFORMATION_HOLDER_

#include "Gamecore.h"

class PauseInformationHolder
{
	PauseInformationHolder() = default;

	~PauseInformationHolder() = default;

	static PauseInformationHolder* _instance;

	//Scene to return too 
	unsigned int _pausedScene = 0;

	void Destroy();

public:

	static PauseInformationHolder& Instance();

	void PausedScene(unsigned int scene);

	unsigned int GetPausedScene();
};

#endif