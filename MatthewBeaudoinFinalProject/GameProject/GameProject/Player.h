// @file: Player.h
//
// @brief: Player moves around using the WASD Key. Collision will prevent them from walking through walls or enemies.
// The collision system prevents the player from moving and forces them backwards based on their last direction until
// they exit the collider. The player can also shoot using the left mouse button. Direction will be determined based
// on where on the screen the mouse is.
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#pragma once
#ifndef _PLAYER_
#define _PLAYER_

#include "GameCore.h"
#include "Bullet.h"

class Player : public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(Player, Component);

    //Controls player movement speed
    float _speed = 5.0f;

    //Reference for the players starting position
    Vec2 _start_pos;

    //Reference for the players boxcollider
    BoxCollider* _collider = nullptr;

    //information about the bullets the player fires
    float _timeBetweenShots = 0.5;
    float _timeBetweenShotsMax = 1;
    float _shotSpeed = 0;

    //Used for dealing with collisions with walls and enemies
    Vec2 _directionOnCollision = Vec2(0, 0);
    bool _colliding = false;
    float _collidingTimer = 1;

public:
    void Initialize() override;

    void Update() override;

    void Load(json::JSON&) override;
};

#endif 


