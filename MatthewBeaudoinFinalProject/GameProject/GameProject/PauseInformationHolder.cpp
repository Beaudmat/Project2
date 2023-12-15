// @file: PauseInformationHolder.cpp
//
// @brief: Singleton design. Allows levels to pass information about themselves to the PauseMenu so the PauseMenu knows
// what scene to return too when the player clicks continue
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#include "GameCore.h"
#include "PauseInformationHolder.h"

PauseInformationHolder* PauseInformationHolder::_instance = nullptr;

void PauseInformationHolder::Destroy()
{
	delete _instance;
}

PauseInformationHolder& PauseInformationHolder::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new PauseInformationHolder();
	}
	return *_instance;
}

//Sets the scene to be returned too on a continue click
void PauseInformationHolder::PausedScene(unsigned int scene)
{
	_pausedScene = scene;
}

//Gets the scene to be returned too on a continue click
unsigned int PauseInformationHolder::GetPausedScene()
{
	return _pausedScene;
}