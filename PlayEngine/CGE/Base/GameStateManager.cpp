#include "Base/GameStateManager.h"
#include <iostream>
#include <chrono>
#include"Graphic/GUI_Overlay.h"
	
GameStateManager* GameStateManager::ptr;

using namespace std::chrono;

GameStateManager::GameStateManager()
{
	platform = PEPlatform::GetPtr();
}

GameStateManager::~GameStateManager()
{
}

GameStateManager* GameStateManager::GetPtr()
{
	if (ptr == nullptr)
	{
		ptr = new GameStateManager();
	}
	return ptr;
}

void GameStateManager::GameLoop()
{
	milliseconds time, oldtime, newtime, frameRateTime;
	frameRateTime = oldtime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	//Para que el juego se cierre al poner ESC
	unsigned int frameRate = 0;
	//UI OVERLAY
	Graphic::GUI_Overlay* gui = Graphic::GUI_Overlay::GetPtr();

	while (!platform->shouldWindowClose())
	{
		try
		{
			newtime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			time = newtime - oldtime;
			
			if (states.size() == 0)
				throw std::exception("Error");
			auto state = states.top();
			if (state == nullptr)
			{
				break;
			}
			
			if (newtime - frameRateTime >= seconds(1))
			{
				std::cout << frameRate << std::endl;
				frameRate = 0;
				frameRateTime = newtime;
			}

			platform->CheckEvent(state, &GameState::Input, &GameState::MouseInput);

			state->Update(time.count());
			platform->RenderClear();
			state->Draw();
			//DIBUJAR EL GUI OVERLAY AQUI
			gui->Draw();
			platform->RenderPresent();
			frameRate++;
			

			oldtime = newtime;
		}
		catch (...)
		{
			std::cout << "Critical error App is closing";
			break;
		}
	}
}

void GameStateManager::SetState(GameState* state)
{
	state->Init();
	states.push(state);
}

void GameStateManager::RealaseState()
{
	auto state = states.top();
	state->Close();
	states.pop();
}