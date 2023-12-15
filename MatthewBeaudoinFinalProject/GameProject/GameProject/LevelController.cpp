// @file: LevelController.cpp
//
// @brief: Checks if the player has hit the pause button and transfers them to the pause menu
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#include "GameCore.h"
#include "LevelController.h"
#include "PauseMenu.h"
#include "PauseInformationHolder.h"

IMPLEMENT_DYNAMIC_CLASS(LevelController);

void LevelController::Initialize()
{
	
}

void LevelController::Update()
{
	//If the ~ key was hit it sends the player to the pause scene
	if (InputSystem::Instance().isKeyPressed(SDLK_BACKQUOTE))
	{
		Scene* currentScene = SceneManager::Get().GetActiveScene();
		PauseInformationHolder::Instance().PausedScene(GetHashCode(currentScene->GetGUID().c_str()));
		if (SceneManager::Get().SetActiveScene(_pauseScene))
		{
			currentScene->isEnabled = false;
		}
	}
}

void LevelController::Load(json::JSON& document)
{
	//Scene the player is sent to when they hit ~
	if (document.hasKey("PauseScene"))
	{
		_pauseScene = GetHashCode(document["PauseScene"].ToString().c_str());
	}
}