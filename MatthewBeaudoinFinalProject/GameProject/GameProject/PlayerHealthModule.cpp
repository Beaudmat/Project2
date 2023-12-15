// @file: PlayerHealthModule.cpp
//
// @brief: Tracks the players lives. It will updated the livesUI and sends the player back to the main menu on death
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#include "GameCore.h"
#include "PlayerHealthModule.h"

IMPLEMENT_DYNAMIC_CLASS(PlayerHealthModule);

void PlayerHealthModule::Initialize()
{
	//Pulls the LivesCounter for future reference
	//std::list<Entity*> livesEntity = ownerEntity->GetParentScene()->FindEntityByName("LivesUI");
	//_livesUI = (FontSprite*)livesEntity.front()->GetComponent("FontSprite");
}

void PlayerHealthModule::Update()
{
	//If lives reach zero the player is sent back to the main menu
	if (_lives <= 0)
	{
		Scene* currentScene = SceneManager::Get().GetActiveScene();
		if (SceneManager::Get().SetActiveScene(_menuScene))
		{
			currentScene->isEnabled = false;
		}
	}
}

void PlayerHealthModule::Load(json::JSON& document)
{
	if (document.hasKey("Lives"))
	{
		_lives = document["Lives"].ToInt();
	}
	if (document.hasKey("MenuScene"))
	{
		_menuScene = GetHashCode(document["MenuScene"].ToString().c_str());
	}
}

//Decreases players lives and updates the livesUI
void PlayerHealthModule::DecreaseLives()
{
	_lives -= 1;
}