// @file: EnemyBullet.h
//
// @brief: Moves towards the provided position and destroys itself on collisions. Deals damage to the enemies if it
// collides with one of them. 
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#pragma once
#ifndef _ENEMY_BULLET_
#define _ENEMY_BULLET_

#include "GameCore.h"

class EnemyBullet : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(EnemyBullet, Component);

	Vec2 _direction = Vec2(0, 0);

	float _speed = 50;

	//Holds onto the collider for future reference
	BoxCollider* _collider = nullptr;

	//Tells the bullet to destroy itself
	bool _destroyBullet = false;

	float _damage = 25;

public:

	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;

	void SetDirection(Vec2 direction);

	void SetSpeed(float speed);

	float GetDamage();
};

#endif