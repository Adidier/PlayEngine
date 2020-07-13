#pragma once
#include "CGE/Base/GameState.h"
#include "CGE/Base/GameStateManager.h"
#include "CGE/Graphic/Mesh.h"
#include "CGE/Graphic/Shader.h"
#include "CGE/Base/ShaderManager.h"
#include "CGE/Graphic/Model.h"
#include "CGE/Graphic/Skybox.h"
#include "Player.h"
#include "Enemy.h"
#include<vector>

class Game : public GameState
{
private:
	Platform* platform;
	GameStateManager* manager;
	ShaderManager* shaderManager;
	Skybox *skybox;
	Player player;
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
	void LoadModels(const std::vector<std::string> &pathFileModels);
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