#include "GameCore.h"
#include "UiColorer.h"
#include "FontSprite.h"

IMPLEMENT_DYNAMIC_CLASS(UiColorer);

void UiColorer::Initialize()
{
	FontSprite* uiElement = (FontSprite*)ownerEntity->GetComponent("FontSprite");

	uiElement->SetFontColor(_textColor.r, _textColor.g, _textColor.b, _textColor.a);
}

void UiColorer::Update()
{

}

void UiColorer::Load(json::JSON& document)
{
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