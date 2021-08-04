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
	physics = Physics::GetPtr();
	physics->InitPhysics();
	std::cout << " Menu Init" << std::endl;
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::GetPtr();
	resourceManager = ResourceManager::GetPtr();
	
	std::map<std::string, std::string> paths = {
	{"Enemy","Assets/Models/pina_pose.obj"},
	{"Wall1","Assets/Models/lWall.obj"},
	{"Wall2","Assets/Models/rWall.obj"},
	{"Player","Assets/Models/pina_pose.obj"},
	};
	//LoadModels(paths);

	auto resourceManger = ResourceManager::GetPtr();
	resourceManger->Add(ResourceType::Model3d, "Floor", "Assets/Models/floor2.obj");
	resourceManger->Add(ResourceType::Model3d, "Container", "Assets/Models/Container.obj");
	resourceManger->Add(ResourceType::Model3d, "Enemy", "Assets/Models/pina_pose.obj");
	resourceManger->Add(ResourceType::Model3d, "Wall", "Assets/Models/Wall.obj");
	//resourceManger->Add(ResourceType::Model3d, "Robot", "Assets/Models/robot.obj");
	resourceManger->Add(ResourceType::Texture, "TEXTURE",  "Assets/Textures/pina.png");
	resourceManger->Add(ResourceType::Texture, "TEXTURE", "Assets/Textures/brick.png");
	resourceManger->Add(ResourceType::Texture, "TEXTURE", "Assets/Textures/ContainerAlbedo.png");
	//resourceManger->Add(ResourceType::Texture, "TEXTURE", "Assets/Textures/RobbiDiffuse.png");
	//Aquí agrego los modelos y tecturas
	resourceManger->Add(ResourceType::Music, "MUSIC", "Assets/Sounds/funnysong.wav");
	resourceManger->Add(ResourceType::Sound, "SHOTSOUND", "Assets/Sounds/laser_shot.wav");
	resourceManger->Add(ResourceType::GUILine, "IMAGE", "Assets/Textures/montanas.png");


	resourceManger->Wait();
	
	
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

	resourceManger->Load();
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_ft.tga");
	skybox = new Skybox(skyboxFaces);

	gui = new Graphic::GUI((Graphic::IGUILayer*)resourceManager->GetElement("LINE", "line"),
		player->GetCamera(), shaderManager);

	std::vector<std::string> pathsEnemies = {
	"Enemy1",
	"Enemy2",
	};
	LoadEnemies(pathsEnemies);
	LoadMusic();
}

void Game::LoadEnemies(const std::vector<std::string>& pathFileModels)
{
	for (int i=0;i<20;i++)
	{
		Enemy* enemy = new Enemy(player);
		enemies.push_back(enemy);
	}
}

void Game::LoadModels(const std::map<std::string, std::string> &models)
{
	for (auto model : models)
	{
		auto resourceManger = ResourceManager::GetPtr();
		resourceManger->Add(ResourceType::Model3d, model.first, model.second);
		auto asset = (Model*)ResourceManager::GetPtr()->GetElement(model.first, model.second);
		asset->AddTexture("Assets/Textures/brick.png");
		map.push_back(asset);
	}
}

void Game::LoadMusic()
{
	auto asset = (MusicPlayer*)ResourceManager::GetPtr()->GetElement("MUSIC", "Assets/Sounds/funnysong.wav");
	asset->PlayMusic();
}

void Game::LoadShaders()
{
	
}

void Game::Draw()
{
	skybox->Draw(shaderManager->GetViewMatrix(), shaderManager->GetProjectionMatrix());

	shaderManager->Activate("toon-shader");
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
/*

render de una imagen sobre el contexto de OpenGL HUD-- Max
arreglar box colliders ---- Walter
agregar biblioteca sonido ---- Alfredo
cargar un conjunto de modelos para hacer un mapa basico con box colliders --Pao 

2 parcial

*/