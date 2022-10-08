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
#include "Cube.h"
#include "Sphere.h"
#include "Floor.h"
#include "Level.h"
#include "Wall.h"
#include "Physics/Physics.h"
#include "Graphic/GUI.h"
#include "Graphic/GUILine.h"
#include "Graphic/Lights/DirectionalLight.h"
#include "Graphic/Lights/PointLight.h"
#include "Audio/AudioPlayer.h"
#include "Audio/MusicPlayer.h"
#include <vector>
#include <list>

class Game : public GameState
{
private:
	Platform* platform;
	GameStateManager* manager;
	ResourceManager* resourceManager;
	ShaderManager* shaderManager;
	Skybox *skybox;
	Physics *physics;
	
	Player* player;
	std::list<Cube*> boxes;
	Floor* floor;

	DirectionalLight directionalLight;
	PointLight point1;
	PointLight point2;
	PointLight point3;

	float sec = 0;
public:
	Game();
	~Game();
	void Init() override;
	void Draw() override;
	bool Input(std::map<int, bool> keys) override;
	bool MouseInput(int x, int y, bool leftbutton);
	void Update(unsigned int delta) override;
	void Close() override;
	void LoadShaders();
	void LoadModels(const std::map<std::string, std::string>& models);
	static void InitResources();
};
