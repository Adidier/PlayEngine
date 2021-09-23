#include "Base/GameStateManager.h"
#include "LoadScreen.h"
#include "Game.h"




int main(int argc, char* argv[])
{
	GameStateManager* manager = GameStateManager::GetPtr();

	manager->SetState(new LoadScreen());

	manager->GameLoop();
	return 0;
}
