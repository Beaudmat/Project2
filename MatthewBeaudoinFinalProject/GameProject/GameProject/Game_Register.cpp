#include "GameCore.h"
#include "UiColorer.h"
#include "MainMenu.h"
#include "LevelTimer.h"
#include "Bullet.h"
#include "MapGenerator.h"

void GameRegisterClasses()
{
	REGISTER_TYPECLASS(Player);
	REGISTER_TYPECLASS(GameOver);
	REGISTER_TYPECLASS(UiColorer);
	REGISTER_TYPECLASS(MainMenu);
	REGISTER_TYPECLASS(LevelTimer);
	REGISTER_TYPECLASS(Bullet);
	REGISTER_TYPECLASS(MapGenerator)
}