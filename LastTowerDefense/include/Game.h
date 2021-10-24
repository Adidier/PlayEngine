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
#include "Level.h"
#include "Wall.h"
#include "Physics/Physics.h"
#include "Graphic/GUI.h"
#include "Graphic/GUILine.h"
#include "Audio/AudioPlayer.h"
#include "Audio/MusicPlayer.h"
#include<vector>

class Game : public GameState
{
private:
	float theta = 0;
	Platform* platform;
	GameStateManager* manager;
	ResourceManager* resourceManager;
	ShaderManager* shaderManager;
	Skybox *skybox;
	Player *player;
	std::vector<Graphic::Model*> map;
	Physics *physics;

	Graphic::GUI* weaponUI;
	Graphic::GUI* playerUI;

	std::vector<Enemy*> enemies;
	Level* level;
	Wall* wall;
	Wall* wall1;
	Wall* wall2;
	Wall* wall3;
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
	void LoadMusic();
	static void InitResources();
};
