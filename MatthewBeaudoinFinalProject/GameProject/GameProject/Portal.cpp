#include "GameCore.h"
#include "Portal.h"

IMPLEMENT_DYNAMIC_CLASS(Portal);

void Portal::Initialize() 
{
	_collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
}

void Portal::Update()
{
	for (const auto & other : _collider->OnCollisionEnter())
	{
		if (other->GetOwner()->GetName() == "Player")
		{
			Scene* currentScene = SceneManager::Get().GetActiveScene();
			if (SceneManager::Get().SetActiveScene(_nextScene))
			{
				currentScene->isEnabled = false;
			}
		}
	}
}

void Portal::Load(json::JSON& document)
{
	if (document.hasKey("NextScene"))
	{
		_nextScene = GetHashCode(document["NextScene"].ToString().c_str());
	}
}