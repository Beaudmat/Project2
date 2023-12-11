#include "GameCore.h"
#include "LevelTimer.h"

IMPLEMENT_DYNAMIC_CLASS(LevelTimer);

void LevelTimer::Initialize()
{
	_levelTimerText = (FontSprite*)ownerEntity->GetComponent("FontSprite");
	UiColorer* colorer = (UiColorer*)ownerEntity->GetComponent("UiColorer");
	_textCurrentColor = colorer->GetTextColor();
}

void LevelTimer::Update()
{
	_levelTimer -= 1 * Time::Instance().DeltaTime();
	_levelTimerText->SetText("Time Left: " + std::to_string((int)_levelTimer));

	if (_levelTimer < 6 && _levelTimer > 0)
	{
		_levelTimerText->SetFontColor(255, 0, 0, 255);
	}
	else if (_levelTimer <= 0)
	{
		Scene* currentScene = SceneManager::Get().GetActiveScene();
		if (SceneManager::Get().SetActiveScene(_sceneOnTimeout))
		{
			_levelTimerText->SetFontColor(_textCurrentColor.r, _textCurrentColor.g, 
				_textCurrentColor.b, _textCurrentColor.a);
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