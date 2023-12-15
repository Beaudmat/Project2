#pragma once
#ifndef _PLAYER_
#define _PLAYER_

#include "GameCore.h"
#include "Bullet.h"

class Player : public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(Player, Component)

    float _speed = 5.0f;
    Vec2 _start_pos;
    BoxCollider* _collider = nullptr;

    float _timeBetweenShots = 0.5;
    float _timeBetweenShotsMax = 5;
    float _shotSpeed = 0;

    Vec2 _previousPosition = Vec2(0, 0);
    Vec2 _directionOnCollision = Vec2(0, 0);
    bool _colliding = false;

    std::list<Bullet*> _bullets;
    std::list<Entity*> _bulletsToDestroy;
    int _bulletPoolSize = 10;

public:
    void Initialize() override;

    void Update() override;

    void Load(json::JSON&) override;
};

#endif 


