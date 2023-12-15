// @file: UiColorer.cpp
//
// @brief: Changes the color for the fontsprite it is attached too
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#include "GameCore.h"
#include "UiColorer.h"
#include "FontSprite.h"

IMPLEMENT_DYNAMIC_CLASS(UiColorer);

void UiColorer::Initialize()
{
	//Pulls the fontsprite its connected too
	FontSprite* uiElement = (FontSprite*)ownerEntity->GetComponent("FontSprite");

	//Sets the color
	uiElement->SetFontColor(_textColor.r, _textColor.g, _textColor.b, _textColor.a);
}

void UiColorer::Update()
{

}

void UiColorer::Load(json::JSON& document)
{
	//Pulls the color it should set the Font too
	if (document.hasKey("TextColor"))
	{
		json::JSON subObject = document["TextColor"];

		if (subObject.hasKey("R"))
		{
			_textColor.r = subObject["R"].ToInt();
		}
		if (subObject.hasKey("G"))
		{
			_textColor.g = subObject["G"].ToInt();
		}
		if (subObject.hasKey("B"))
		{
			_textColor.b = subObject["B"].ToInt();
		}
		if (subObject.hasKey("A"))
		{
			_textColor.a = subObject["A"].ToInt();
		}
	}
}

SDL_Color UiColorer::GetTextColor()
{
	return _textColor;
}