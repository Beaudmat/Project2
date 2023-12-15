// @file: SkeletonController.cpp
//
// @brief: Skeletons will move towards the player then stop short and attack
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#include "GameCore.h"
#include "SkeletonController.h"
#include "Bullet.h"

IMPLEMENT_DYNAMIC_CLASS(SkeletonController);

void SkeletonController::Initialize()
{
	//Holds onto the player Entity for future reference
	_player = ownerEntity->GetParentScene()->FindEntity("uwu");

	//Holds onto the Entities Sprite for future reference
	_sprite = (Sprite*)ownerEntity->GetComponent("Sprite");

	//Holds onto the enemy health module for future reference
	_healthModule = (EnemyHealthModule*)ownerEntity->GetComponent("EnemyHealthModule");

	//Holds onto the box collider for future reference
	_collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
}

void SkeletonController::Update()
{
	//Grabs the direction towards the player
	Vec2 direction = _player->GetTransform().position - ownerEntity->GetTransform().position;
	direction.Normalize();

	//Move towards the player until the stop distance is reached
	if (Vec2::Distance(_player->GetTransform().position, ownerEntity->GetTransform().position) > _stopDistance && !_colliding)
	{
		//Moves the ghost in the direction of the player
		ownerEntity->GetTransform().position += direction * _movementSpeed * Time::Instance().DeltaTime();
	}

	//Decides what sprite should be used based on the position in relation to the player
	if (direction.x > direction.y)
	{
		if (direction.y < 0)
		{
			_sprite->SetTextureAsset(_backward);
		}
		else
		{
			_sprite->SetTextureAsset(_forward);
		}
	}
	else
	{
		if (direction.x < 0)
		{
			_sprite->SetTextureAsset(_left);
		}
		else
		{
			_sprite->SetTextureAsset(_right);
		}
	}

	//Checks if the skeleton has collided with a bullet
	for (const auto& other : _collider->OnCollisionEnter())
	{
		if (other->GetOwner()->GetName() == "PlayerBullet")
		{
			//Decreases the skeletons health by the damage of the bullet
			Bullet* playerBullet = (Bullet*)other->GetOwner()->GetComponent("Bullet");
			_healthModule->DecreaseHealth(playerBullet->GetDamage());
		}
		if (other->GetOwner()->GetName() == "Wall" || other->GetOwner()->GetName() == "Enemy")
		{
			//Direction on collision will be used to move the skeleton back. It won't accept if its a zero direction
			if (direction != Vec2::Zero)
			{
				_directionOnCollision = direction;
			}

			//If were colliding it locks down skeleton movement
			_colliding = true;
		}
	}

	//If the skeleton has exited the collision it lets the skeleton regain control of their movement
	for (const auto& other : _collider->OnCollisionExit())
	{
		if (other->GetOwner()->GetName() == "Wall" || other->GetOwner()->GetName() == "Enemy")
		{
			_colliding = false;
			_collidingTimer = 2;
			break;
		}
	}

	//Makes sure the skeleton doesn't get stuck backing up
	if (_collidingTimer <= 0)
	{
		_colliding = false;
		_collidingTimer = 2;
	}

	//Moves the skeleton backwards from their last previously good direction vector if they are colliding
	if (_colliding)
	{
		_collidingTimer -= 1 * Time::Instance().DeltaTime();
		ownerEntity->GetTransform().position -= _directionOnCollision * (_movementSpeed * 0.25) * Time::Instance().DeltaTime();
	}
}

void SkeletonController::Load(json::JSON& document)
{
	//Pulls the sprite information for the different directions
	if (document.hasKey("FrontFacingSprite"))
	{
		_forward = (TextureAsset*)AssetManager::Get().GetAsset(GetHashCode(document["FrontFacingSprite"].ToString().c_str()));
	}
	if (document.hasKey("BackFacingSprite"))
	{
		_backward = (TextureAsset*)AssetManager::Get().GetAsset(GetHashCode(document["BackFacingSprite"].ToString().c_str()));
	}
	if (document.hasKey("LeftFacingSprite"))
	{
		_left = (TextureAsset*)AssetManager::Get().GetAsset(GetHashCode(document["LeftFacingSprite"].ToString().c_str()));
	}
	if (document.hasKey("RightFacingSprite"))
	{
		_right = (TextureAsset*)AssetManager::Get().GetAsset(GetHashCode(document["RightFacingSprite"].ToString().c_str()));
	}

	//Pulls the Skeleton information
	if (document.hasKey("MovementSpeed"))
	{
		_movementSpeed = document["MovementSpeed"].ToFloat();
	}
	if (document.hasKey("StopDistance"))
	{
		_stopDistance = document["StopDistance"].ToFloat();
	}
}