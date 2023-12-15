#pragma once
#ifndef _PORTAL_
#define _PORTAL_

#include "GameCore.h"

class Portal : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Portal, Component);

	unsigned int _nextScene = 0;
	BoxCollider* _collider = nullptr;

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif