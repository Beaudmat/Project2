// @file: KillCounter.cpp
//
// @brief: Tracks player kills and alters the kill count in the UI
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#include "GameCore.h"
#include "KillCounter.h"

IMPLEMENT_DYNAMIC_CLASS(KillCounter);

void KillCounter::Initialize()
{
	//Holds onto the fontsprite for future reference
	_killsUI = (FontSprite*)ownerEntity->GetComponent("FontSprite");
}

void KillCounter::Update()
{

}

void KillCounter::Load(json::JSON& document)
{

}

//Increases the killcount and changes the UI text
void KillCounter::IncreaseKillCount()
{
	_killCount++;
	_killsUI->SetText("Kills: " + std::to_string(_killCount));
}

int KillCounter::GetKillCount()
{
	return _killCount;
}