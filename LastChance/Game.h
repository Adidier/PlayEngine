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
#include "Floor.h"
#include "Physics/Physics.h"
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
	Physics *physics;

	std::vector<Enemy*> enemies;

	Floor* floor;
public:
	Game();
	~Game();
	void Init() override;
	void Draw() override;
	void DrawMap();
	void DrawEnemies();
	bool Input(std::map<int, bool> keys) override;
	bool MouseInput(int x, int y, bool leftbutton);
	void Update(unsigned int delta) override;
	void Close() override;
	void LoadShaders();
	void LoadModels(const std::map<std::string, std::string>& models);
	void LoadEnemies(const std::vector<std::string>& pathFileModels);
};
