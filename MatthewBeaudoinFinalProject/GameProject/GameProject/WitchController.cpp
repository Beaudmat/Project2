// @file:WitchController.cpp
//
// @brief: Witches will move towards the player however will stop far away and shoot projectiles at them
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#include "GameCore.h"
#include "WitchController.h"
#include "EnemyBullet.h"

IMPLEMENT_DYNAMIC_CLASS(WitchController);

void WitchController::Initialize()
{
	//Holds the player Entity for future reference
	_player = ownerEntity->GetParentScene()->FindEntity("uwu");

	//Hold the Entities Sprite for future reference
	_sprite = (Sprite*)ownerEntity->GetComponent("Sprite");

	//Holds onto the enemy health module for future reference
	_healthModule = (EnemyHealthModule*)ownerEntity->GetComponent("EnemyHealthModule");

	//Holds onto the box collider for future reference
	_collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");

	//Used for dealing with collisions with walls and other enemies
	Vec2 _directionOnCollision = Vec2(0, 0);
	bool _colliding = false;
	float _collidingTimer = 2;
}

void WitchController::Update()
{
	//Grabs the direction towards the player
	Vec2 direction = _player->GetTransform().position - ownerEntity->GetTransform().position;
	direction.Normalize();

	//Witch will keep moving towards the player until they reach the stop distance
	if (Vec2::Distance(_player->GetTransform().position, ownerEntity->GetTransform().position) > _stopDistance && !_colliding)
	{
		//Moves the Witch in the direction of the player
		ownerEntity->GetTransform().position += direction * _movementSpeed * Time::Instance().DeltaTime();
	}
	else
	{
		if (_timeBetweenShots <= 0)
		{
			//Generates a new Entity then sets the name, positioning and sizing
			Entity* bulletEntity = ownerEntity->GetParentScene()->CreateEntity();
			bulletEntity->SetName("EnemyBullet");
			bulletEntity->GetTransform().Scale(Vec2(0.2, 0.2));
			bulletEntity->GetTransform().position = ownerEntity->GetTransform().position;

			//Adds a sprite to the new Entity and sets its information
			Sprite* bulletSprite = (Sprite*)bulletEntity->CreateComponent("Sprite");
			bulletSprite->SetTextureAsset(_bullet);
			bulletSprite->SetFilterColor(0, 11, 255, 255);

			//Adds a box collider to the new Entity
			bulletEntity->CreateComponent("BoxCollider");

			//Adds a Bullet Component to the new Entity then calculates the direction to the player
			EnemyBullet* bullet = (EnemyBullet*)bulletEntity->CreateComponent("EnemyBullet");
			Vec2 direction = _player->GetTransform().position - ownerEntity->GetTransform().position;
			direction.Normalize();
			bullet->SetDirection(direction);
			bullet->SetSpeed(_shotSpeed);

			//Resets the shot timer
			_timeBetweenShots = _timeBetweenShotsMax;
		}
	}

	//Decides what Sprite should be used based on the position of the Witch in relation to the player
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

	//Decreases the timer for shots
	if (_timeBetweenShots > 0)
	{
		_timeBetweenShots -= 1 * Time::Instance().DeltaTime();
	}

	//Checks if the witch has collided with a bullet
	for (const auto& other : _collider->OnCollisionEnter())
	{
		if (other->GetOwner()->GetName() == "PlayerBullet")
		{
			//Decreases the witches health by the damage of the bullet
			Bullet* playerBullet = (Bullet*)other->GetOwner()->GetComponent("Bullet");
			_healthModule->DecreaseHealth(playerBullet->GetDamage());
		}
		if (other->GetOwner()->GetName() == "Wall" || other->GetOwner()->GetName() == "Enemy")
		{
			//Direction on collision will be used to move the witch back. It won't accept if its a zero direction
			if (direction != Vec2::Zero)
			{
				_directionOnCollision = direction;
			}

			//If were colliding it locks down witch movement
			_colliding = true;
		}
	}

	//If the witch has exited the collision it lets the player regain control of their movement
	for (const auto& other : _collider->OnCollisionExit())
	{
		if (other->GetOwner()->GetName() == "Wall" || other->GetOwner()->GetName() == "Enemy")
		{
			_colliding = false;
			_collidingTimer = 2;
			break;
		}
	}

	//Makes sure the witch doesnt get stuck backing up
	if (_collidingTimer <= 0)
	{
		_colliding = false;
		_collidingTimer = 2;
	}

	//Moves the witch backwards from their last previously good direction vector if they are colliding
	if (_colliding)
	{
		_collidingTimer -= 1 * Time::Instance().DeltaTime();
		ownerEntity->GetTransform().position -= _directionOnCollision * (_movementSpeed * 0.25) * Time::Instance().DeltaTime();
	}
}

void WitchController::Load(json::JSON& document)
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

	//Pulls Witch information
	if (document.hasKey("TimeBetweenShots"))
	{
		_timeBetweenShotsMax = document["TimeBetweenShots"].ToFloat();
	}
	if (document.hasKey("ShotSpeed"))
	{
		_shotSpeed = document["ShotSpeed"].ToFloat();
	}
	if (document.hasKey("StopDistance"))
	{
		_stopDistance = document["StopDistance"].ToFloat();
	}
	if (document.hasKey("MovementSpeed"))
	{
		_movementSpeed = document["MovementSpeed"].ToFloat();
	}

	//Pulls the sprite information for the bullet
	if (document.hasKey("BulletSprite"))
	{
		_bullet = (TextureAsset*)AssetManager::Get().GetAsset(GetHashCode(document["BulletSprite"].ToString().c_str()));
	}
}