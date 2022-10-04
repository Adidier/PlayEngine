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
}

void Game::InitResources()
{
	auto resourceManager = ResourceManager::GetPtr();
	resourceManager->Add(ResourceType::Model3d, "floor");
	resourceManager->Add(ResourceType::Model3d, "floor2");
	resourceManager->Add(ResourceType::Model3d, "floor3");
	resourceManager->Add(ResourceType::Model3d, "container");
	resourceManager->Add(ResourceType::Model3d, "pina_pose");
	resourceManager->Add(ResourceType::Model3d, "wall");
	resourceManager->Add(ResourceType::Model3d, "cube");
	resourceManager->Add(ResourceType::Model3d, "sphere");
	resourceManager->Add(ResourceType::Model3d, "cylinder");

	resourceManager->Add(ResourceType::Texture, "pina_normal");
	resourceManager->Add(ResourceType::Texture, "pina");
	resourceManager->Add(ResourceType::Texture, "brick");
	resourceManager->Add(ResourceType::Texture, "brick2");
	resourceManager->Add(ResourceType::Texture, "ContainerAlbedo");
	resourceManager->Add(ResourceType::Texture, "bricknormal");

	resourceManager->Add(ResourceType::Music, "funnysong");
	resourceManager->Add(ResourceType::Sound, "laser_shot");

	resourceManager->Add(ResourceType::ImageUI, "montanas");
	resourceManager->Add(ResourceType::ImageUI, "montanas2");
	resourceManager->Add(ResourceType::ImageUI, "montanas3");
	
	resourceManager->Wait();
	
}

void Game::Init()
{
	physics = Physics::GetPtr();
	physics->InitPhysics();
	std::cout << " Menu Init" << std::endl;
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::GetPtr();
	resourceManager = ResourceManager::GetPtr();

	resourceManager->Load();
	player = new Player();
	floor = new Floor();
	cube = new Cube();
	sphere = new Sphere();
	cylinder = new Cylinder();

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
	weaponUI = new Graphic::GUI((Graphic::IGUILayer*)resourceManager->GetElement("montanas2"), player->GetCamera(), shaderManager);
	playerUI = new Graphic::GUI((Graphic::IGUILayer*)resourceManager->GetElement("montanas"), player->GetCamera(), shaderManager);
	new Graphic::GUI((Graphic::IGUILayer*)resourceManager->GetElement("montanas3"), player->GetCamera(), shaderManager);

	std::vector<std::string> pathsEnemies = {
		"Enemy1",
		"Enemy2"
	};

	LoadMusic();
}

void Game::LoadMusic()
{
	auto asset = (MusicPlayer*)ResourceManager::GetPtr()->GetElement("funnysong");
	//asset->PlayMusic();
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
	DrawEnemies();
	floor->Draw();
	cube->Draw();
	sphere->Draw();
	cylinder->Draw();
}
void Game::DrawMap()
{
	for (auto model : map)
	{
		Transform transform;
		transform.SetTranslation(0.0f, 0.0f, 0.0f);
		transform.SetScale(1.0f, 1.0f, 1.0f);
		transform.SetRotation(0, 0, 0);
		model->SetTransform(transform);
		model->Draw();
	}
}

void Game::DrawEnemies()
{
	for (auto enemi : enemies)
	{
		enemi->Draw();
	}
}

void Game::Update(unsigned int delta)
{
	floor->Update(delta);
	for (auto enemi : enemies)
	{
		enemi->Update(delta);
	}

	cube->Update(delta);
	sphere->Update(delta);
	cylinder->Update(delta);
	physics->Update(delta);
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
	player->GetCamera()->keyControl(keys, platform->GetDeltaTime());
	return false;
}

void Game::Close()
{
	std::cout << " Close Init" << std::endl;
}
