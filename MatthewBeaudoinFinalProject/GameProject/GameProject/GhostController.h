#pragma once
#ifndef _GHOST_CONTROLLER_
#define _GHOST_CONTROLLER_

#include "GameCore.h"

class GhostController : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(GhostController, Component);

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif