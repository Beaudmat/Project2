#include "GameCore.h"
#include "GhostController.h"

IMPLEMENT_DYNAMIC_CLASS(GhostController);

void GhostController::Initialize()
{
	name = "Enemy";
}

void GhostController::Update()
{
	ownerEntity->GetTransform().position.x += 1;
}

void GhostController::Load(json::JSON& document)
{

}