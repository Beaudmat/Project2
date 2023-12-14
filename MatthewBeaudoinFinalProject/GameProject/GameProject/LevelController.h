#pragma once
#ifndef _LEVEL_CONTROLLER_
#define _LEVEL_CONTROLLER_

#include "GameCore.h"

class LevelController : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(LevelController, Component);

	unsigned int _pauseScene = 0;

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif