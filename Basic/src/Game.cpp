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

	delete player;
}

void Game::InitResources()
{
	auto resourceManager = ResourceManager::GetPtr();
	resourceManager->Add(ResourceType::Model3d, "floor");
	resourceManager->Add(ResourceType::Model3d, "cube");
	resourceManager->Add(ResourceType::Model3d, "sphere");
	resourceManager->Add(ResourceType::Model3d, "pina_pose");

	resourceManager->Add(ResourceType::Texture, "pina_normal");
	resourceManager->Add(ResourceType::Texture, "pina");
	resourceManager->Add(ResourceType::Texture, "brick");
	resourceManager->Add(ResourceType::Texture, "brick2");
	resourceManager->Add(ResourceType::Texture, "ContainerAlbedo");
	resourceManager->Add(ResourceType::Texture, "bricknormal");

	resourceManager->Wait();	
}

void Game::Init()
{
	physics = Physics::GetPtr();
	physics->InitPhysics();
	std::cout << " Game Init" << std::endl;
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::GetPtr();
	resourceManager = ResourceManager::GetPtr();

	resourceManager->Load();

	player = new Player();
	floor = new Floor();
	baseFloor = new BaseFloor();
	model = new Cube(1);
	LoadShaders();
	shaderManager = ShaderManager::GetPtr();
	new Graphic::GUI((Graphic::IGUILayer*)resourceManager->GetElement("montanas3"), player->GetCamera(), shaderManager);
}

void Game::LoadShaders()
{
	shaderManager = ShaderManager::GetPtr();
	shaderManager->InitShader(player->GetCamera());
	shaderManager->LoadShaders("phong-shader");

}

void Game::Draw()
{
	shaderManager->Activate("phong-shader");
	shaderManager->draw();

	model->Draw();
	floor->Draw();
	baseFloor->Draw();
}

void Game::Update(unsigned int delta)
{
	auto current = shaderManager->GetCurrentShader();
	current->SetUniform("myMaterialDiffuse", glm::vec3(1, 0, 0.3216));
	floor->Update(delta);
	model->Update(delta);

	physics->Update(delta);
	
	angle += 0.001f;

}

bool Game::MouseInput(int x, int y, bool leftbutton)
{
	if (x != -1 || y != -1)//TODO fix
	{
		player->GetCamera()->mouseControl(x, y);
	}
	physics->RaycastScreen(x, y, player->GetCamera()->getCameraPosition());
	return false;
}

bool Game::Input(std::map<int, bool> keys)
{

	return false;
}

void Game::Close()
{
	std::cout << " Close Init" << std::endl;
}
