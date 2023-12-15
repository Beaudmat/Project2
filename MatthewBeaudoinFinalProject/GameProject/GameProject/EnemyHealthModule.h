// @file: EnemyHealthModule.h
//
// @brief: Tracks the enemies health. It will tell the KillCounter to increase when an enemy dies and tell
// the spawner to decrease its enemyCount.
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#pragma once
#ifndef _ENEMY_HEALTH_MODULE_
#define _ENEMY_HEALTH_MODULE_

#include "Gamecore.h"
#include "KillCounter.h"
#include "Spawner.h"

class EnemyHealthModule : public Component {
	DECLARE_DYNAMIC_DERIVED_CLASS(EnemyHealthModule, Component);

    //Enemy health
    float _health;

    //How many points the enemy is worth when its killed
    float _pointReward;

    //Holds onto the KillCounter for future reference
    KillCounter* _killsCounter = nullptr;

    //Holds onto the BoxCollider for future reference
    BoxCollider* _collider = nullptr;

    //Holds onto the Spawner for future reference
    Spawner* _spawner = nullptr;

public:
    void Initialize() override;

    void Update() override;

    void Load(json::JSON&) override;

    void DecreaseHealth(float decrease);

    void DecreaseToZero();

    //Enemy doesn't know what spawner it is coming from so it must be set
    void SetSpawner(Spawner* spawner);
};


#endif