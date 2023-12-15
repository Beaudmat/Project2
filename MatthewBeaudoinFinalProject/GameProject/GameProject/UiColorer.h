// @file: UiColorer.cpp
//
// @brief: Changes the color for the fontsprite it is attached too
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#pragma once
#ifndef _UI_COLORER_
#define _UI_COLORER_

#include "GameCore.h"

class UiColorer : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(UiColorer, Component);

	//Pulls color from load
	SDL_Color _textColor = { 255,255,255,255 };

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;

	SDL_Color GetTextColor();
};

#endif