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

void PauseInformationHolder::PausedScene(unsigned int scene)
{
	_pausedScene = scene;
}

unsigned int PauseInformationHolder::GetPausedScene()
{
	return _pausedScene;
}