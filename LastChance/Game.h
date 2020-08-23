#pragma once
#include "Base/GameState.h"
#include "Base/GameStateManager.h"
#include "Graphic/Mesh.h"
#include "Graphic/Shader.h"
#include "Base/ShaderManager.h"
#include "Base/ResourceManager.h"
#include "Graphic/Model.h"
#include "Graphic/Skybox.h"
#include "Player.h"
#include "Enemy.h"
#include<vector>

class Game : public GameState
{
private:
	PEPlatform* platform;
	GameStateManager* manager;
	ResourceManager* resourceManager;
	ShaderManager* shaderManager;
	Skybox *skybox;
	Player *player;
	std::vector<Model*> map;

	std::vector<Enemy*> enemies;

public:
	Game();
	~Game();
	void Init() override;
	void Draw() override;
	void DrawMap();
	void DrawEnemies();
	bool Input(std::map<int, bool> keys) override;
	bool MouseInput(int x, int y, bool leftbutton);
	void Update() override;
	void Close() override;
	void LoadShaders();
	void LoadModels(const std::map<std::string, std::string>& models);
	void LoadEnemies(const std::vector<std::string>& pathFileModels);
};

/*
	std::vector<Mesh*> meshList;
	Texture* mainTexture;
	Texture* rTexture;
	Texture* gTexture;
	Texture* bTexture;
	Texture* blendTexture;
	Texture* normalTexture;

	Model* model1;
	Model* model2;

	Transform transformModel1;
	Transform transformModel2;

*/