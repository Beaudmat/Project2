#include "GameCore.h"
#include "Bullet.h"

IMPLEMENT_DYNAMIC_CLASS(Bullet);

void Bullet::Initialize()
{
	name = "Bullet";
}

void Bullet::Update()
{
	ownerEntity->GetTransform().position += _direction * _speed * Time::Instance().DeltaTime();
}

void Bullet::Load(json::JSON& document)
{
	if (document.hasKey("Speed"))
	{
		_speed = document["Speed"].ToFloat();
	}
}

void Bullet::SetDirection(Vec2 direction)
{
	_direction = direction;
}

void Bullet::SetSpeed(float speed)
{
	_speed = speed;
}