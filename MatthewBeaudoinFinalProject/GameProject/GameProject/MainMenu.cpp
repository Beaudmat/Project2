#include "GameCore.h"
#include "MainMenu.h"
#include "Entity.h"

IMPLEMENT_DYNAMIC_CLASS(MainMenu)

void MainMenu::Initialize()
{
	//Sets the main menus background color
	RenderSystem::Instance().WindowBackgroundColor(_backgroundColor.r, _backgroundColor.g,
		_backgroundColor.b, _backgroundColor.a);

	//Pulls the playbutton so MainMenu can interact with it
	std::list<Entity*> buttons = ownerEntity->GetParentScene()->FindEntityByName("PlayButton");
	_playButton = (Sprite*)buttons.front()->GetComponent("Sprite");

	buttons.clear();

	//Pulls the loadbutton so MainMenu can interact with it
	buttons = ownerEntity->GetParentScene()->FindEntityByName("LoadButton");
	_loadButton = (Sprite*)buttons.front()->GetComponent("Sprite");
}

void MainMenu::Update()
{
	//Grabs Mouse Position
	int x, y;
	SDL_GetMouseState(&x, &y);

	//Grabs Button Positions
	Vec2 playButtonPos = _playButton->GetOwner()->GetTransform().position;
	Vec2 loadButtonPos = _loadButton->GetOwner()->GetTransform().position;

	//Checks if the players mouse is over the Play Button
	if (x < playButtonPos.x + 115 && x > playButtonPos.x - 120 && y < playButtonPos.y + 35 && y > playButtonPos.y - 45)
	{
		_playButton->SetFilterColor(_highlightColor.r, _highlightColor.g, _highlightColor.b, _highlightColor.a);
		if (InputSystem::Instance().isMouseButtonPressed(SDL_BUTTON_LEFT))
		{
			Scene* currentScene = SceneManager::Get().GetActiveScene();
			if (SceneManager::Get().SetActiveScene(_playLevel))
			{
				currentScene->isEnabled = false;
			}
		}
	}
	else
	{
		_playButton->SetFilterColor(255, 255, 255, 255);
	}

	//Checks if player mouse is over the Load Button
	if (x < loadButtonPos.x + 115 && x > loadButtonPos.x - 120 && y < loadButtonPos.y + 35 && y > loadButtonPos.y - 45)
	{
		_loadButton->SetFilterColor(_highlightColor.r, _highlightColor.g, _highlightColor.b, _highlightColor.a);
	}
	else
	{
		_loadButton->SetFilterColor(255, 255, 255, 255);
	}
}

void MainMenu::Load(json::JSON& document)
{
	//Loads Background Color Information
	if (document.hasKey("BackgroundColor"))
	{
		json::JSON subObject = document["BackgroundColor"];

		if (subObject.hasKey("R"))
		{
			_backgroundColor.r = subObject["R"].ToInt();
		}
		if (subObject.hasKey("G"))
		{
			_backgroundColor.g = subObject["G"].ToInt();
		}
		if (subObject.hasKey("B"))
		{
			_backgroundColor.b = subObject["B"].ToInt();
		}
		if (subObject.hasKey("A"))
		{
			_backgroundColor.a = subObject["A"].ToInt();
		}
	}

	//Loads Button Highlight Information
	if (document.hasKey("HighlightColor"))
	{
		json::JSON subObject = document["HighlightColor"];

		if (subObject.hasKey("R"))
		{
			_highlightColor.r = subObject["R"].ToInt();
		}
		if (subObject.hasKey("G"))
		{
			_highlightColor.g = subObject["G"].ToInt();
		}
		if (subObject.hasKey("B"))
		{
			_highlightColor.b = subObject["B"].ToInt();
		}
		if (subObject.hasKey("A"))
		{
			_highlightColor.a = subObject["A"].ToInt();
		}
	}

	//Grabs the scene to be loaded when the play button is hit
	if (document.hasKey("PlayLevel"))
	{
		_playLevel = GetHashCode(document["PlayLevel"].ToString().c_str());
	}
}