#pragma once
#ifndef _BULLET_
#define _BULLET_

#include "GameCore.h"

class Bullet : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Bullet, Component);

public:

	void Initialize() override;

	void Update() override;

	void Load(json::JSON& document) override;

	void SetDirection(Vec2 direction);

	void SetSpeed(float speed);

	bool CheckCollision();

private:

	Vec2 _direction = Vec2(0, 0);

	float _speed = 50;

	BoxCollider* _collider = nullptr;

	bool _destroyBullet = false;
};

#endif
