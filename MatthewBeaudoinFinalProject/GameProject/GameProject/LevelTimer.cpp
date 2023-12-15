// @file: LevelTimer.cpp
//
// @brief: Tracks the time the player has been in the level. It decreases and when it reaches zero it sends the player
// back to the main menu. It also updates the color of the text based on the time remaining.
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#include "GameCore.h"
#include "LevelTimer.h"

IMPLEMENT_DYNAMIC_CLASS(LevelTimer);

void LevelTimer::Initialize()
{
	_levelTimerText = (FontSprite*)ownerEntity->GetComponent("FontSprite");

	//Grabs the current color of the font so it can be restored when the timer is done
	UiColorer* colorer = (UiColorer*)ownerEntity->GetComponent("UiColorer");
	_textCurrentColor = colorer->GetTextColor();
}

void LevelTimer::Update()
{
	//Decreases the timer and updates the UI
	_levelTimer -= 1 * Time::Instance().DeltaTime();
	_levelTimerText->SetText("Time Left: " + std::to_string((int)_levelTimer));

	//If the time is close to done the font color updates to red
	if (_levelTimer < 6 && _levelTimer > 0)
	{
		_levelTimerText->SetFontColor(255, 0, 0, 255);
	}
	else if (_levelTimer <= 0)
	{
		//If the timer has run out the player is sent back to the main menu
		Scene* currentScene = SceneManager::Get().GetActiveScene();
		if (SceneManager::Get().SetActiveScene(_sceneOnTimeout))
		{
			//Resets the font color to what it was orginally
			_levelTimerText->SetFontColor(_textCurrentColor.r, _textCurrentColor.g, 
				_textCurrentColor.b, _textCurrentColor.a);

			//Resets the timer
			_levelTimer = _levelTimerMax;

			currentScene->isEnabled = false;
		}
	}
}

void LevelTimer::Load(json::JSON& document)
{
	if (document.hasKey("LevelTime"))
	{
		_levelTimer = document["LevelTime"].ToFloat();
		_levelTimerMax = _levelTimer;
	}

	if (document.hasKey("SceneOnTimeout"))
	{
		_sceneOnTimeout = GetHashCode(document["SceneOnTimeout"].ToString().c_str());
	}
}