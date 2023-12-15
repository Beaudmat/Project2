// @file: Portal.cpp
//
// @brief: Transfers the player to the next level
//
// @author: Matthew Beaudoin
// @date: 2023-12-13

#include "GameCore.h"
#include "Portal.h"

IMPLEMENT_DYNAMIC_CLASS(Portal);

void Portal::Initialize() 
{
	//Holds onto the collider for future reference
	_collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
}

void Portal::Update()
{
	//Checks if we collided with the player. If we did it transfers us to the next scene
	for (const auto & other : _collider->OnCollisionEnter())
	{
		if (other->GetOwner()->GetName() == "Player")
		{
			Scene* currentScene = SceneManager::Get().GetActiveScene();
			if (SceneManager::Get().SetActiveScene(_nextScene))
			{
				currentScene->isEnabled = false;
				LOG(SceneManager::Get().GetActiveScene());
			}
		}
	}
}

void Portal::Load(json::JSON& document)
{
	//Scene player will be sent to when they collide with the portal
	if (document.hasKey("NextScene"))
	{
		_nextScene = GetHashCode(document["NextScene"].ToString().c_str());
	}
}