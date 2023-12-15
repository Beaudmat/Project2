#include "GameCore.h"
#include "Bullet.h"

IMPLEMENT_DYNAMIC_CLASS(Bullet);

void Bullet::Initialize()
{
	_collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
}

void Bullet::Update()
{
	ownerEntity->GetTransform().position += _direction * _speed * Time::Instance().DeltaTime();

	for (const auto& other : _collider->OnCollisionEnter())
	{
		if (other->GetOwner()->GetName() == "Enemy")
		{
			_destroyBullet = true;
			break;
		}
	}

	if (_destroyBullet)
	{
		if (_collider != nullptr) {
			CollisionSystem::Instance().ClearCollisions((ICollider*)ownerEntity->GetComponent("BoxCollider"));
			//ownerEntity->RemoveComponent(ownerEntity->GetComponent("BoxCollider"));
			ownerEntity->GetParentScene()->RemoveEntity(ownerEntity->GetGuid());
		}
	}
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

bool Bullet::CheckCollision()
{
	if (_collider == nullptr)
	{
		LOG("COLLIDER IS NULL");
	}
	else
	{
		for (const auto& other : _collider->OnCollisionEnter())
		{
			if (other->GetOwner()->GetName() == "Enemy")
			{
				LOG("STRUCK ENEMY IN HEAD");
				return true;
			}
		}
	}
	return false;
}