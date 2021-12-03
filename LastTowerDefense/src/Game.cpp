#include "Game.h"
#include<iostream>
#include <glm.hpp>
#include <time.h>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>


Game::Game() : directionalLight(glm::vec3(20, 10, 0), glm::vec3(0, 1, 0),
					glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), 40),
			  point1(0, glm::vec3(0,0,0), glm::vec3(0, 0, 1),
				  glm::vec3(0, 0, 1), glm::vec3(0, 0, 1),.01f,.009f,.005f),
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
	level = new Level();
	wall = new Wall();
	wall->setTransform(0, 50, -600, 0);
	wall1 = new Wall();
	wall1->setTransform(0, 50, 600, 0);
	wall2 = new Wall();
	wall2->setTransform(600, 50, 0, -1.57f );
	wall3 = new Wall();
	wall3->setTransform(-600, 50, 0, 1.57f);

	LoadShaders();
	
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("../../Resources/Assets/Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("../../Resources/Assets/Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("../../Resources/Assets/Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("../../Resources/Assets/Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("../../Resources/Assets/Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("../../Resources/Assets/Textures/Skybox/cupertin-lake_ft.tga");
	skybox = new Skybox(skyboxFaces);		
	shaderManager = ShaderManager::getPtr();
	weaponUI = new Graphic::GUI((Graphic::IGUILayer*)resourceManager->GetElement("montanas2"), player->GetCamera(), shaderManager);
	playerUI = new Graphic::GUI((Graphic::IGUILayer*)resourceManager->GetElement("montanas"), player->GetCamera(), shaderManager);
	new Graphic::GUI((Graphic::IGUILayer*)resourceManager->GetElement("montanas3"), player->GetCamera(), shaderManager);

	std::vector<std::string> pathsEnemies = {
		"Enemy1",
		"Enemy2"
	};

	LoadEnemies(pathsEnemies);
	LoadMusic();


}

void Game::LoadEnemies(const std::vector<std::string>& pathFileModels)
{
	for (int i=0;i<1;i++)
	{
		Enemy* enemy = new Enemy(player);
		enemies.push_back(enemy);
	}
}

void Game::LoadMusic()
{
	auto asset = (MusicPlayer*)ResourceManager::GetPtr()->GetElement("funnysong");
	//asset->PlayMusic();
}

void Game::LoadShaders()
{
	shaderManager = ShaderManager::getPtr();
	shaderManager->initShader(player->GetCamera());
	//shaderManager->LoadShaders("ADSL");
	shaderManager->LoadShaders("phong-shader-lighting");
	//shaderManager->LoadShaders("bumpmapping");
	//shaderManager->LoadShaders("toon-shader");
	//shaderManager->LoadShaders("gui");
	//shaderManager->LoadShaders("ADSL");
	//shaderManager->LoadShaders("Sobel");
}

void Game::Draw()
{
	//skybox->Draw(shaderManager->GetViewMatrix(), shaderManager->GetProjectionMatrix());

	shaderManager->Activate("phong-shader-lighting");
	shaderManager->draw();
	glm::vec3 position (30*cos(theta), 10, 30 * sin(theta));
	//directionalLight.UseLight();
	auto currentShader = shaderManager->GetCurrentShader();
	/*currentShader->SetUniform("diffuseMap", 0);
	currentShader->SetUniform("normalMap", 1);
	currentShader->SetUniform("lightPosition", position);
	*/

	currentShader->SetUniform("material.difuse", 0);
	currentShader->SetUniform("material.specular", 1);
	currentShader->SetUniform("material.shininess", 400.0f);

	point1.UseLight();
	point2.UseLight();
	point3.UseLight();

	theta += 0.01;
	DrawMap();
	DrawEnemies();
	floor->Draw();/*
	level->Draw();
	wall->Draw();
	wall1->Draw();
	wall2->Draw();
	wall3->Draw();*/
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
	level->Update(delta);
	wall->Update(delta);
	wall1->Update(delta);
	wall2->Update(delta);
	wall3->Update(delta);
	for (auto enemi : enemies)
	{
		enemi->Update(delta);
	}
	physics->Update(delta);
}

bool Game::MouseInput(int x, int y, bool leftbutton)
{
	if (x != -1 || y != -1)
	{
		player->GetCamera()->mouseControl(x, y);
	}		
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
