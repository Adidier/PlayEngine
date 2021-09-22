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

void Game::InitResources()
{
	auto resourceManager = ResourceManager::GetPtr();
	resourceManager->Add(ResourceType::Model3d, "floor");
	resourceManager->Add(ResourceType::Model3d, "floor2");
	resourceManager->Add(ResourceType::Model3d, "floor3");
	resourceManager->Add(ResourceType::Model3d, "container");
	resourceManager->Add(ResourceType::Model3d, "pina_pose");
	resourceManager->Add(ResourceType::Model3d, "wall");

	resourceManager->Add(ResourceType::Texture, "pina");
	resourceManager->Add(ResourceType::Texture, "brick");
	resourceManager->Add(ResourceType::Texture, "ContainerAlbedo");

	resourceManager->Add(ResourceType::Music, "funnysong");
	resourceManager->Add(ResourceType::Sound, "laser_shot");

	resourceManager->Add(ResourceType::ImageUI, "montanas1");
	resourceManager->Add(ResourceType::ImageUI, "montanas2");
	resourceManager->Add(ResourceType::ImageUI, "montanas3");

	resourceManager->Wait();

	resourceManager->Load();
}

void Game::Init()
{
	resourceManager = ResourceManager::GetPtr();
	physics = Physics::GetPtr();
	physics->InitPhysics();
	std::cout << " Menu Init" << std::endl;
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::GetPtr();

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

	shaderManager = ShaderManager::getPtr();
	shaderManager->initShader(player->GetCamera());
	shaderManager->LoadShaders("OneColor", "Assets/Shaders/OneColor.vert", "Assets/Shaders/OneColor.frag");
	shaderManager->LoadShaders("gouraud-shader", "Assets/Shaders/gouraud-shader.vert", "Assets/Shaders/gouraud-shader.frag");
	shaderManager->LoadShaders("phong-shader", "Assets/Shaders/phong-shader.vert", "Assets/Shaders/phong-shader.frag");
	shaderManager->LoadShaders("toon-shader", "Assets/Shaders/toon-shader.vert", "Assets/Shaders/toon-shader.frag");
	shaderManager->LoadShaders("gui", "Assets/Shaders/gui.vert", "Assets/Shaders/gui.frag");

	
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_ft.tga");
	skybox = new Skybox(skyboxFaces);		

	weaponUI = new Graphic::GUI((Graphic::IGUILayer*)resourceManager->GetElement("montanas2"), player->GetCamera(), shaderManager);
	playerUI = new Graphic::GUI((Graphic::IGUILayer*)resourceManager->GetElement("montanas1"), player->GetCamera(), shaderManager);
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
	for (int i=0;i<10;i++)
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
}

void Game::Draw()
{
	skybox->Draw(shaderManager->GetViewMatrix(), shaderManager->GetProjectionMatrix());

	shaderManager->Activate("phong-shader");
	shaderManager->draw();
	
	DrawMap();
	DrawEnemies();
	floor->Draw();
	level->Draw();
	wall->Draw();
	wall1->Draw();
	wall2->Draw();
	wall3->Draw();
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
	shaderManager->initShader(player->GetCamera());
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

ShaderManager* Game::GetShaderManagerPtr()
{
	return shaderManager;
}

Camera* Game::GetCameraPtr()
{
	return player->GetCamera();
}
/*

render de una imagen sobre el contexto de OpenGL HUD-- Max
arreglar box colliders ---- Walter
agregar biblioteca sonido ---- Alfredo
cargar un conjunto de modelos para hacer un mapa basico con box colliders --Pao 

2 parcial

*/