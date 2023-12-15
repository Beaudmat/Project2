// @file: Bullet.cpp
//
// @brief: Moves towards the provided position and destroys itself on collisions. Deals damage to the enemies if it
// collides with one of them. 
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#include "GameCore.h"
#include "Bullet.h"

IMPLEMENT_DYNAMIC_CLASS(Bullet);

void Bullet::Initialize()
{
	//Holds onto the collider for future reference
	_collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
}

void Bullet::Update()
{
	//Moves towards the position passed from the player
	ownerEntity->GetTransform().position += _direction * _speed * Time::Instance().DeltaTime();

	//Checks for any collisions 
	for (const auto& other : _collider->OnCollisionEnter())
	{
		if (other->GetOwner()->GetName() != "Player")
		{
			_destroyBullet = true;
		}
		if (other->GetOwner()->GetName() == "Enemy")
		{
			break;
		}
	}

	//If it collides with anything it clears out any references to itself in the collisionSystem then destroys itself
	if (_destroyBullet)
	{
		if (_collider != nullptr) {
			CollisionSystem::Instance().ClearCollisions((ICollider*)ownerEntity->GetComponent("BoxCollider"));
			ownerEntity->GetParentScene()->RemoveEntity(ownerEntity->GetGuid());
		}
	}
}

void Bullet::Load(json::JSON& document)
{

}

void Bullet::SetDirection(Vec2 direction)
{
	_direction = direction;
}

void Bullet::SetSpeed(float speed)
{
	_speed = speed;
}

float Bullet::GetDamage()
{
	return _damage;
}