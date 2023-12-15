#pragma once
#ifndef _PAUSE_INFORMATION_HOLDER_
#define _PAUSE_INFORMATION_HOLDER_

#include "Gamecore.h"

class PauseInformationHolder
{
	PauseInformationHolder() = default;

	~PauseInformationHolder() = default;

	static PauseInformationHolder* _instance;

	unsigned int _pausedScene = 0;

	void Destroy();

public:

	static PauseInformationHolder& Instance();

	void PausedScene(unsigned int scene);

	unsigned int GetPausedScene();
};

#endif