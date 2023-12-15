// @file: GhostController.cpp
//
// @brief: Ghosts will chase after the player and destroy themselves on impact damaging the player
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#include "GameCore.h"
#include "GhostController.h"

IMPLEMENT_DYNAMIC_CLASS(GhostController);

void GhostController::Initialize()
{
	//Holds onto the player for future reference
	_player = ownerEntity->GetParentScene()->FindEntity("uwu");

	//Holds the entities sprite for future reference
	_sprite = (Sprite*)ownerEntity->GetComponent("Sprite");
}

void GhostController::Update()
{
	//Grabs the direction towards the player
	Vec2 direction = _player->GetTransform().position - ownerEntity->GetTransform().position;
	direction.Normalize();

	//Moves the ghost in the direction of the player
	ownerEntity->GetTransform().position += direction * _movementSpeed * Time::Instance().DeltaTime();

	//Decides what sprite should be used based on the position of the player in relation to the ghost
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

	//Checks if the Ghost has reached the player and destroys it
	if (Vec2::Distance(_player->GetTransform().position, ownerEntity->GetTransform().position) < 10)
	{
		ownerEntity->GetParentScene()->RemoveEntity(ownerEntity->GetGuid());
	}
}

void GhostController::Load(json::JSON& document)
{
	//Pulls the information for the different Ghost Sprites
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
	
	//Pulls Ghost Information
	if (document.hasKey("MovementSpeed"))
	{
		_movementSpeed = document["MovementSpeed"].ToFloat();
	}
}