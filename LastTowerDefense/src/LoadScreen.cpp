#include "LoadScreen.h"
#include "Game.h"
#include <iostream>
#include <glm.hpp>
#include <time.h>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

bool LoadScreen::isFinish = false;
LoadScreen::LoadScreen()
{
	
}

LoadScreen::~LoadScreen()
{

}

void LoadScreen::Loading()
{
	Game::InitResources();
	isFinish = true;
}

void LoadScreen::Init()
{
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::GetPtr();
	resourceManager = ResourceManager::GetPtr();
	resourceManager->Add(ResourceType::ImageUI, "LoadingScreen");

	resourceManager->Wait();
	resourceManager->Load();

	shaderManager = ShaderManager::getPtr();

	camera = new Camera(glm::vec3(10, 10.7, 100.6f), glm::vec3(0.0f, 1.0f, 0.0f), 3.0f, 3.0f, 355.0f, 0.1f);
	shaderManager->initShader(camera);

	shaderManager->LoadShaders("gui", "Assets/Shaders/gui.vert", "Assets/Shaders/gui.frag");
	loadGUI = new Graphic::GUI((Graphic::IGUILayer*)resourceManager->GetElement("LoadingScreen"), camera, shaderManager);

	load = new thread(&LoadScreen::Loading);
}

void LoadScreen::Draw()
{

}

void LoadScreen::Update(unsigned int delta)
{
	if (load->joinable() && isFinish)
	{
		resourceManager->RemoveLoadResource();
		manager->RealaseState();
		manager->SetState(new Game());
		load->join();
	}
}

bool LoadScreen::MouseInput(int x, int y, bool leftbutton)
{	
	return false;
}

bool LoadScreen::Input(std::map<int, bool> keys)
{	
	return false;
}

void LoadScreen::Close()
{
	delete loadGUI;
	//Graphic::GUIOverlay::GetPtr()->Remove(loadGUI); Error draro de Link...
	std::cout << " Close Init" << std::endl;
}