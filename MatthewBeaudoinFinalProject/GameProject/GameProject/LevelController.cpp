#include "GameCore.h"
#include "LevelController.h"

IMPLEMENT_DYNAMIC_CLASS(LevelController);

void LevelController::Initialize()
{

}

void LevelController::Update()
{
	if (InputSystem::Instance().isKeyPressed(SDLK_BACKQUOTE))
	{
		Scene* currentScene = SceneManager::Get().GetActiveScene();
		if (SceneManager::Get().SetActiveScene(_pauseScene))
		{
			currentScene->isEnabled = false;
		}
	}
}

void LevelController::Load(json::JSON& document)
{
	if (document.hasKey("PauseScene"))
	{
		_pauseScene = GetHashCode(document["PauseScene"].ToString().c_str());
	}
}