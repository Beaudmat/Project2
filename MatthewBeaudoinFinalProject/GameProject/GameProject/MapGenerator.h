// @file: MapGenerator.h
//
// @brief: Reads through a jsonFile containing information about a set of TileID's the user wants to generate. 
// An array of TileID's and CollideableTileID's are pulled along with the the texture to pull the tiles from. 
// The MapGenerator calculates the X Y Coordinats on the texture for the tile and compares the TileID to 
// the CollideableTileID's to see if a collider should be added.
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#pragma once
#ifndef _MAP_GENERATOR_
#define _MAP_GENERATOR_

#include "GameCore.h"

class MapGenerator : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(MapGenerator, Component);

	//The list of TileID's we need to generate
	json::JSON _tiles = json::JSON::Array();

	//The list of TileID's that should have colliders added
	json::JSON _tileIDsWithColliders = json::JSON::Array();

	unsigned int _mapFileGUID = 0;

public:
	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;
};

#endif