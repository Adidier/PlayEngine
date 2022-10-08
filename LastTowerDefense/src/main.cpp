#include "Base/GameStateManager.h"
#include "LoadScreen.h"
#include "Game.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
	srand(time(NULL));
	ResourceManager::GetPtr("../../Resources/Assets");
	GameStateManager* manager = GameStateManager::GetPtr();
	manager->SetState(new LoadScreen());
	manager->GameLoop();
	return 0;
}
