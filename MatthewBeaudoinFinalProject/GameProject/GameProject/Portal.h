// @file: Portal.cpp
//
// @brief: Transfers the player to the next level
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#pragma once
#ifndef _PORTAL_
#define _PORTAL_

#include "GameCore.h"

class Portal : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Portal, Component);

	//Scene the player is sent to when they collide with the portal
	unsigned int _nextScene = 0;

	BoxCollider* _collider = nullptr;

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif