#include "Base/GameStateManager.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	GameStateManager* manager = GameStateManager::GetPtr();
	manager->SetState(new Game());
	manager->GameLoop();
	return 0;
}
