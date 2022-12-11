#include "Game.h"
#include<iostream>
#include <glm.hpp>
#include <time.h>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>


Game::Game() : directionalLight(glm::vec3(20, 10, 0), glm::vec3(0, 1, 0),
					glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), 40),
			  point1(0, glm::vec3(0,0,0), glm::vec3(1, 1, 1),
				  glm::vec3(0, 0, 1), glm::vec3(1, 1, 1),.1f,.009f,.005f),
	point2(1, glm::vec3(-1, 1, -1), glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 1), glm::vec3(1, 0, 1), .01f, .09f, .05f),
	point3(2, glm::vec3(1, 1, 1), glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), .01f, .009f, .005f)
{
}

Game::~Game()
{
	delete floor;
	delete player;
	delete baseFloor;
}

void Game::InitResources()
{
	auto resourceManager = ResourceManager::GetPtr();
	resourceManager->Add(ResourceType::Model3d, "floor");
	resourceManager->Add(ResourceType::Model3d, "cube");
	resourceManager->Add(ResourceType::Model3d, "sphere");
	resourceManager->Add(ResourceType::Model3d, "cylinder");

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
	floor = new Floor(&boxes);
	baseFloor = new BaseFloor();
	boxes.push_back(new Cube(0));
	boxes.push_back(new Cube(1,0));

	LoadShaders();
	
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("../../Resources/Assets/Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("../../Resources/Assets/Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("../../Resources/Assets/Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("../../Resources/Assets/Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("../../Resources/Assets/Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("../../Resources/Assets/Textures/Skybox/cupertin-lake_ft.tga");
	skybox = new Skybox(skyboxFaces);		
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
	skybox->Draw(shaderManager->GetViewMatrix(), shaderManager->GetProjectionMatrix());
	shaderManager->Activate("phong-shader");
	shaderManager->draw();
	for (const auto box : boxes)
	{
		box->Draw();
	}
	floor->Draw();
	baseFloor->Draw();
}

void Game::Update(unsigned int delta)
{
	floor->Update(delta);
	for (const auto box : boxes)
	{
		box->Update(delta);
	}	
	
	physics->Update(delta);
	
	if (spawnCube) 
	{
		timerNextCube -= delta;
	}

	timestamp += delta;

	if (timerNextCube < 0) {
		boxes.push_back(new Cube(timestamp, 0));
		timerNextCube = timeToSpawn;
		spawnCube = false;
	}	
	std::cout << "timerNextCube " << timerNextCube << std::endl;
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
	if (keys[GLFW_KEY_S])
	{
		auto top = boxes.back();
		top->InitRigidBody(1);
		spawnCube = true;
	}
	return false;
}

void Game::Close()
{
	std::cout << " Close Init" << std::endl;
}
