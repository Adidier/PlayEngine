#include "Base/GameStateManager.h"
#include "Game.h"
#include "LoadScreen.h"

int main(int argc, char* argv[])
{
	GameStateManager* manager = GameStateManager::GetPtr();
	manager->SetState(new LoadScreen());
	//manager->SetState(new Game());
	manager->GameLoop();
	return 0;
}
