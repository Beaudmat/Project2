#pragma once
#ifndef _SPAWNER_
#define _SPAWNER_

#include "GameCore.h"

class Spawner : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Spawner, Component);

	float _timeBetweenSpawnsMax = 5;
	float _timeBetweenSpawns = 1;

	int _enemyCountMax = 3;
	int _enemyCount = 0;

public:

	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif