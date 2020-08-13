#include "Base/GameStateManager.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	Base::GameStateManager* manager = Base::GameStateManager::GetPtr();
	manager->SetState(new SourceFiles::Game());
	manager->GameLoop();
	return 0;
}
