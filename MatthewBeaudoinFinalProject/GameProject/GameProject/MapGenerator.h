#pragma once
#ifndef _MAP_GENERATOR_
#define _MAP_GENERATOR_

#include "GameCore.h"

class MapGenerator : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(MapGenerator, Component);

	json::JSON _tiles = json::JSON::Array();

	unsigned int _mapFileGUID = 0;

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif