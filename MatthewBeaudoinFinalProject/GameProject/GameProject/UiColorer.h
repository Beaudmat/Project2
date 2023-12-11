#pragma once
#ifndef _UI_COLORER_
#define _UI_COLORER_

#include "GameCore.h"

class UiColorer : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(UiColorer, Component);

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;

	SDL_Color GetTextColor();

private:
	SDL_Color _textColor = { 255,255,255,255 };
};

#endif