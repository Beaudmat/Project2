#include "GameCore.h"
#include "UiColorer.h"
#include "MainMenu.h"
#include "LevelTimer.h"
#include "Bullet.h"
#include "MapGenerator.h"
#include "Spawner.h"
#include "GhostController.h"
#include "WitchController.h"
#include "SkeletonController.h"
#include "LevelController.h"
#include "PauseMenu.h"
#include "Portal.h"

void GameRegisterClasses()
{
	REGISTER_TYPECLASS(Player);
	REGISTER_TYPECLASS(GameOver);
	REGISTER_TYPECLASS(UiColorer);
	REGISTER_TYPECLASS(MainMenu);
	REGISTER_TYPECLASS(LevelTimer);
	REGISTER_TYPECLASS(Bullet);
	REGISTER_TYPECLASS(MapGenerator);
	REGISTER_TYPECLASS(Spawner);
	REGISTER_TYPECLASS(GhostController);
	REGISTER_TYPECLASS(WitchController);
	REGISTER_TYPECLASS(SkeletonController);
	REGISTER_TYPECLASS(LevelController);
	REGISTER_TYPECLASS(PauseMenu);
	REGISTER_TYPECLASS(Portal);
}