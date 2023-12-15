// @file: PauseMenu.cpp
//
// @brief: Pulls the buttons for the pause menu. Tracks the players mouse and if it goes over top of the buttons they
// are highlighted. Sends the player to the correct scene if the button is clicked.
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#include "GameCore.h"
#include "PauseMenu.h"
#include "PauseInformationHolder.h"

IMPLEMENT_DYNAMIC_CLASS(PauseMenu);

void PauseMenu::Initialize()
{
	//Pulls the continue button so PauseMenu can interact with it
	std::list<Entity*> buttons = ownerEntity->GetParentScene()->FindEntityByName("ContinueButton");
	_continueButton = (Sprite*)buttons.front()->GetComponent("Sprite");

	buttons.clear();

	//Pulls the save button so PauseMenu can interact with it
	buttons = ownerEntity->GetParentScene()->FindEntityByName("SaveButton");
	_saveButton = (Sprite*)buttons.front()->GetComponent("Sprite");

	buttons.clear();

	//Pulls the quit button so PauseMenu can interact with it
	buttons = ownerEntity->GetParentScene()->FindEntityByName("QuitButton");
	_quitButton = (Sprite*)buttons.front()->GetComponent("Sprite");
}

void PauseMenu::Update()
{
	//Grabs Mouse Position
	int x, y;
	SDL_GetMouseState(&x, &y);

	//Grabs Button Positions
	Vec2 continueButtonPos = _continueButton->GetOwner()->GetTransform().position;
	Vec2 quitButtonPos = _quitButton->GetOwner()->GetTransform().position;
	Vec2 saveButtonPos = _saveButton->GetOwner()->GetTransform().position;

	//Checks if the players mouse is over the continue Button
	if (x < continueButtonPos.x + 115 && x > continueButtonPos.x - 120 
		&& y < continueButtonPos.y + 35 && y > continueButtonPos.y - 45)
	{
		_continueButton->SetFilterColor(_highlightColor.r, _highlightColor.g, _highlightColor.b, _highlightColor.a);
		if (InputSystem::Instance().isMouseButtonPressed(SDL_BUTTON_LEFT))
		{
			Scene* currentScene = SceneManager::Get().GetActiveScene();
			//Pulls the sceen that was paused from the PauseInformationHolder singleton
			if (SceneManager::Get().SetActiveScene(PauseInformationHolder::Instance().GetPausedScene()))
			{
				currentScene->isEnabled = false;
			}
		}
	}
	else
	{
		_continueButton->SetFilterColor(255, 255, 255, 255);
	}

	//Checks if player mouse is over the Load Button
	if (x < saveButtonPos.x + 115 && x > saveButtonPos.x - 120 && y < saveButtonPos.y + 35 && y > saveButtonPos.y - 45)
	{
		_saveButton->SetFilterColor(_highlightColor.r, _highlightColor.g, _highlightColor.b, _highlightColor.a);
	}
	else
	{
		_saveButton->SetFilterColor(255, 255, 255, 255);
	}

	//Checks if player mouse is over the Load Button
	if (x < quitButtonPos.x + 115 && x > quitButtonPos.x - 120 && y < quitButtonPos.y + 35 && y > quitButtonPos.y - 45)
	{
		_quitButton->SetFilterColor(_highlightColor.r, _highlightColor.g, _highlightColor.b, _highlightColor.a);
		if (InputSystem::Instance().isMouseButtonPressed(SDL_BUTTON_LEFT))
		{
			Scene* currentScene = SceneManager::Get().GetActiveScene();
			if (SceneManager::Get().SetActiveScene(_quitScene))
			{
				currentScene->isEnabled = false;
			}
		}
	}
	else
	{
		_quitButton->SetFilterColor(255, 255, 255, 255);
	}
}

void PauseMenu::Load(json::JSON& document)
{
	if (document.hasKey("QuitScene"))
	{
		_quitScene = GetHashCode(document["QuitScene"].ToString().c_str());
	}
}