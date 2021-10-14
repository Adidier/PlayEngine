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

class LoadScreen : public GameState
{
private:
	static bool isFinish;
	std::thread* load;
	Platform* platform;
	Camera* camera;
	GameStateManager* manager;
	ResourceManager* resourceManager;
	ShaderManager* shaderManager;
	Skybox *skybox;

public:
	LoadScreen();
	~LoadScreen();
	static void Loading();
	void Init() override;
	void Draw() override;
	bool Input(std::map<int, bool> keys) override;
	bool MouseInput(int x, int y, bool leftbutton);
	void Update(unsigned int delta) override;
	void Close() override;
};
