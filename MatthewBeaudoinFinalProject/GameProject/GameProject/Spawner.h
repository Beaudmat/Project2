// @file: Spawner.h
//
// @brief: Generates new entities, gives them a randomly decidied enemy controller and passes along associated data
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#pragma once
#ifndef _SPAWNER_
#define _SPAWNER_

#include "GameCore.h"

class Spawner : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Spawner, Component);

	//Time between new enemies being created
	float _timeBetweenSpawnsMax = 5;
	float _timeBetweenSpawns = 1;

	//Maxmium number of enemies allowed
	int _enemyCountMax = 3;
	int _enemyCount = 0;

	//Holds the data for the different enemy types
	json::JSON _ghostData = json::JSON::Object();
	json::JSON _witchData = json::JSON::Object();
	json::JSON _skeletonData = json::JSON::Object();

public:

	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif