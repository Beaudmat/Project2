#include "GameCore.h"
#include "UiColorer.h"
#include "MainMenu.h"
#include "LevelTimer.h"

void GameRegisterClasses()
{
	REGISTER_TYPECLASS(Player);
	REGISTER_TYPECLASS(GameOver);
	REGISTER_TYPECLASS(UiColorer);
	REGISTER_TYPECLASS(MainMenu);
	REGISTER_TYPECLASS(LevelTimer);
}