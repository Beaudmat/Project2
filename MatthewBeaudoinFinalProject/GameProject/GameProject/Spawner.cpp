#include "GameCore.h"
#include "Spawner.h"
#include "Sprite.h"

IMPLEMENT_DYNAMIC_CLASS(Spawner);

void Spawner::Initialize()
{
	BoxCollider* myCollider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
	myCollider->SetSize(6000, 6000);
}

void Spawner::Update()
{
	if (_timeBetweenSpawns > 0)
	{
		_timeBetweenSpawns -= 1 * Time::Instance().DeltaTime();
	}
	else if (_timeBetweenSpawns <= 0 && _enemyCount < _enemyCountMax)
	{
		Entity* newEnemy = ownerEntity->GetParentScene()->CreateEntity();
		newEnemy->GetTransform().Scale(Vec2(0.2, 0.2));
		newEnemy->GetTransform().position.x = ownerEntity->GetTransform().position.x;
		newEnemy->GetTransform().position.y = ownerEntity->GetTransform().position.y;

		Sprite* enemySprite = (Sprite*)newEnemy->CreateComponent("Sprite");
		enemySprite->SetTextureAsset((TextureAsset*)AssetManager::Get().GetAsset("68h3hfh6di287hfu388cfi3"));

		newEnemy->CreateComponent("BoxCollider");

		newEnemy->CreateComponent("GhostController");
		
		_timeBetweenSpawns = _timeBetweenSpawnsMax;

		_enemyCount++;
	}
}

void Spawner::Load(json::JSON& document)
{
	if (document.hasKey("TimeBetweenSpawns"))
	{
		_timeBetweenSpawnsMax = document["TimeBetweenSpawns"].ToFloat();
	}
	if (document.hasKey("EnemyCountMax"))
	{
		_enemyCountMax = document["EnemyCountMax"].ToInt();
	}
}