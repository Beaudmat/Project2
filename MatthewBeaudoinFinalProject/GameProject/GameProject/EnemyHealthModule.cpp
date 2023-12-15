// @file: EnemyHealthModule.cpp
//
// @brief: Tracks the enemies health. It will tell the KillCounter to increase when an enemy dies and tell
// the spawner to decrease its enemyCount.
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#include "GameCore.h"
#include "EnemyHealthModule.h"

IMPLEMENT_DYNAMIC_CLASS(EnemyHealthModule);

void EnemyHealthModule::Initialize()
{
	//Pulls the KillCounter for future reference
	std::list<Entity*> killsEntity = ownerEntity->GetParentScene()->FindEntityByName("KillsUI");
	_killsCounter = (KillCounter*)killsEntity.front()->GetComponent("KillCounter");

	//Pulls the collider for future reference
	_collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
}

void EnemyHealthModule::Update()
{
	if (_health <= 0)
	{
		//Updates the KillCounter and Spawner
		_killsCounter->IncreaseKillCount();
		_spawner->EnemyDied();

		//Clears out any active collisions and removes the enemy
		CollisionSystem::Instance().ClearCollisions((ICollider*)_collider);
		ownerEntity->GetParentScene()->RemoveEntity(ownerEntity->GetGuid());
	}
}

void EnemyHealthModule::Load(json::JSON& document)
{
	if (document.hasKey("Health"))
	{
		_health = document["Health"].ToFloat();
	}
	if (document.hasKey("PointValue"))
	{
		_pointReward = document["PointValue"].ToFloat();
	}
}

void EnemyHealthModule::DecreaseHealth(float decrease)
{
	_health -= decrease;
}

void EnemyHealthModule::DecreaseToZero()
{
	_health = 0;
}

//Enemy doesn't know what spawner its coming from so it must be passed
void EnemyHealthModule::SetSpawner(Spawner* spawner)
{
	_spawner = spawner;
}