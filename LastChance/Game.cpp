#include "Game.h"
#include<iostream>
#include <glm.hpp>
#include <time.h>
#include "Physics/Physics.h"
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

namespace SourceFiles {
	Game::Game() : player("adidier regresa.obj")
	{

	}

	Game::~Game()
	{
	}

	void Game::Init()
	{
		std::cout << " Menu Init" << std::endl;
		this->platform = Base::PEPlatform::GetPtr();
		this->manager = Base::GameStateManager::GetPtr();

		shaderManager = Base::ShaderManager::getPtr();
		shaderManager->initShader(player.GetCamera());
		shaderManager->LoadShaders("OneColor", "Assets/Shaders/OneColor.vert", "Assets/Shaders/OneColor.frag");
		shaderManager->LoadShaders("gouraud-shader", "Assets/Shaders/gouraud-shader.vert", "Assets/Shaders/gouraud-shader.frag");
		shaderManager->LoadShaders("phong-shader", "Assets/Shaders/phong-shader.vert", "Assets/Shaders/phong-shader.frag");
		shaderManager->LoadShaders("toon-shader", "Assets/Shaders/toon-shader.vert", "Assets/Shaders/toon-shader.frag");

		std::vector<std::string> skyboxFaces;
		skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_rt.tga");
		skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_lf.tga");
		skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_up.tga");
		skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_dn.tga");
		skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_bk.tga");
		skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_ft.tga");
		skybox = new Graphics::Skybox(skyboxFaces);

		std::vector<std::string> paths = {
			"Assets/Models/lWall.obj",
			"Assets/Models/rWall.obj",
		};
		LoadModels(paths);

		std::vector<std::string> pathsEnemies = {
		"Assets/Models/pina_pose.obj"
		};
		LoadEnemies(pathsEnemies);
	}

	void Game::LoadEnemies(const std::vector<std::string>& pathFileModels)
	{
		for (auto path : pathFileModels)
		{
			SourceFiles::Enemy* enemy = new SourceFiles::Enemy(&player, path);
			enemies.push_back(enemy);
		}
	}

	void Game::LoadModels(const std::vector<std::string>& pathFileModels)
	{
		for (auto path : pathFileModels)
		{
			Graphics::Model* model = new Graphics::Model();
			model->LoadModel(path);
			model->AddTexture("Assets/Textures/brick.png");
			map.push_back(model);
		}
	}

	void Game::LoadShaders()
	{

	}

	void Game::Draw()
	{
		platform->RenderClear();
		skybox->Draw(shaderManager->GetViewMatrix(), shaderManager->GetProjectionMatrix());

		shaderManager->Activate("phong-shader");
		shaderManager->draw();

		DrawMap();
		DrawEnemies();

		platform->RenderPresent();
	}
	void Game::DrawMap()
	{
		for (auto model : map)
		{
			Base::Transform transform;
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

	void Game::Update()
	{

		for (auto enemi : enemies)
		{
			enemi->Update();
		}
	}

	bool Game::MouseInput(int x, int y, bool leftbutton)
	{
		if (x != -1 || y != -1)
			player.GetCamera()->mouseControl(x, y);
		return false;
	}

	bool Game::Input(std::map<int, bool> keys)
	{
		bool ok = false;
		for (auto model : map)
		{
			auto vertexModel1BB = model->GetMesh()->UpdateBoundingBox(glm::mat4(1));
			if (Physics::Physics::CheckColision(vertexModel1BB, player.GetBoundingBox()))
			{
				ok = true;
			}
		}
		if (!ok) {
			player.GetCamera()->keyControl(keys, platform->GetDeltaTime());
		}

		return false;
	}



	void Game::Close()
	{
		std::cout << " Close Init" << std::endl;
	}
}

/*

model1 = new Model();
	model1->LoadModel("Assets/Models/pina_pose.obj");
	model1->AddTexture("pina.png");
	model1->AddTexture("pina_normal.png");

	model2 = new Model();
	model2->LoadModel("Assets/Models/pina_pose.obj");
	model2->AddTexture("pina.png");
	model2->AddTexture("pina_normal.png");


	srand(time(NULL));
	angle = 0;


		unsigned int indices[] = {
				0,1,2,
				1,2,3,
	};

	std::vector<GLfloat> vertices = {
		// floor
		-1.0, -1.0,  -1.0, 0.0f, 0.0f,		0.0f, 0.0f, 0.8f,1.0f, 0.0f, 0.0f,//0
		-1.0, -1.0,  1.0,0.0f, 1.0f,		0.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,//1
		1.0,  -1.0,  -1.0,1.0f, 0.0f,		0.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,//2
		1.0,  -1.0,  1.0,1.0f, 1.0f,		0.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,//3
	};
	//calcAverageNormals(indices, 6, vertices, 44, 11, 5);
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 44, 6, 11);
	meshList.push_back(obj1);

	mainTexture = new Texture("Assets/Textures/MultiTexture/mainTexture.png");
	mainTexture->LoadTexture();
	rTexture = new Texture("Assets/Textures/MultiTexture/rTexture.png");
	rTexture->LoadTexture();
	gTexture = new Texture("Assets/Textures/MultiTexture/gTexture.png");
	gTexture->LoadTexture();
	bTexture = new Texture("Assets/Textures/MultiTexture/bTexture.png");
	bTexture->LoadTexture();
	blendTexture = new Texture("Assets/Textures/MultiTexture/blendTexture.png");
	blendTexture->LoadTexture();
	normalTexture = new Texture("Assets/Textures/MultiTexture/bricknormal.png");
	normalTexture->LoadTexture();


	glm::mat4 model(1);
	GLint uniformModel = shaderManager->GetUniformId("model");
	model = glm::translate(model, glm::vec3(0.0f, -10.0f, -2.5f));
	model = glm::scale(model, glm::vec3(100.0f, 10.0f, 100.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	mainTexture->UseTexture(GL_TEXTURE0);
	//rTexture->UseTexture(GL_TEXTURE1);
	//gTexture->UseTexture(GL_TEXTURE2);
	//bTexture->UseTexture(GL_TEXTURE3);
	//blendTexture->UseTexture(GL_TEXTURE4);
	normalTexture->UseTexture(GL_TEXTURE1);

	//glUniform1i(shaderManager->GetmainTex(), 0);
	//glUniform1i(shaderManager->GetrTex(), 1);
	//glUniform1i(shaderManager->GetgTex(), 2);
	//glUniform1i(shaderManager->GetbTex(), 3);
	//glUniform1i(shaderManager->GetblendTexture(), 4);
	//glUniform1i(shaderManager->GetNormalTexture(), 5);


	meshList[0]->RenderMesh();

	//
	//shaderManager->Activate("phong-shader");
	//shaderManager->draw();
	//uniformModel = shaderManager->GetModelLocation();
	//GLint color1 = shaderManager->GetColor1();
	//GLint color2 = shaderManager->GetColor2();
	//model = glm::translate(model, glm::vec3(10.0f, 0.0f, -8.5f));
	//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//glUniform3f(color1, 0, angle, 0.0f );
	//angle = angle + 1.0f;
	//glUniform3f(color2, 0.0f, 0.0f, 1.0f);

	//meshList[0]->RenderMesh();

	shaderManager->Activate("phong-shader");
	shaderManager->draw();
	transformModel1.SetTranslation(3.0f, 3.0f, 0.0f);
	transformModel1.SetScale(1.1f, 1.1f, 1.11f);
	transformModel1.SetRotation(0, 0, 0);
	model1->SetTransform(&transformModel1);
	model1->Draw();

	transformModel2.SetTranslation(0.0f, 0.0f, 0.0f);
	transformModel2.SetScale(1.1f, 1.1f, 1.11f);
	transformModel2.SetRotation(90, 0, 0);
	model2->SetTransform(&transformModel2);
	model2->Draw();

	auto vertexModel1BB = model1->GetMesh()->UpdateBoundingBox(transformModel1.GetTransform());
	auto vertexModel2BB = model2->GetMesh()->UpdateBoundingBox(transformModel2.GetTransform());
	bool ok = Physics::CheckColision(vertexModel1BB, vertexModel2BB);

*/