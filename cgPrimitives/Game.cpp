#include "Game.h"
#include<iostream>
#include <glm.hpp>
#include <time.h>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>


Game::Game()
{

}

Game::~Game()
{
}

void Game::Init()
{
	std::cout << " Menu Init" << std::endl;
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::GetPtr();
	resourceManager = ResourceManager::GetPtr();
	
	auto resourceManger = ResourceManager::GetPtr();
	resourceManger->Add(ResourceType::GUILine, "Line");

	resourceManger->Wait();
	player = new Player();

	LoadShaders();

	resourceManger->Load();
	m_image = (Graphic::GUILine*) resourceManager->GetElement("Line");
	srand(time(NULL));
	gui = new Graphic::GUI(m_image, player->GetCamera(), shaderManager);
}

void Game::LoadShaders()
{
	shaderManager = ShaderManager::getPtr();
	shaderManager->initShader(player->GetCamera());
	shaderManager->LoadShaders("gui", "Assets/Shaders/gui.vert", "Assets/Shaders/gui.frag");
}

void Game::Draw()
{
	shaderManager->draw();
}

void Game::Update(unsigned int delta)
{
	for (int i=0; i<200; i++)
	m_image->PutPixel(rand()%1024, rand() % 1024, rand() % 255, rand() % 255, rand() % 255, 255);

	m_image->Load();
}

bool Game::MouseInput(int x, int y, bool leftbutton)
{
	if (x != -1 || y != -1)
		player->GetCamera()->mouseControl(x, y);
	return false;
}

bool Game::Input(std::map<int, bool> keys)
{
	player->GetCamera()->keyControl(keys, platform->GetDeltaTime());
	
	return false;
}

void Game::Close()
{
	std::cout << " Close Init" << std::endl;
}
