#pragma once
#include "Base/GameState.h"
#include "Base/GameStateManager.h"
#include "Graphic/Mesh.h"
#include "Graphic/Shader.h"
#include "Base/ShaderManager.h"
#include "Graphic/Model.h"
#include "Graphic/Skybox.h"
#include "Player.h"
#include "Enemy.h"
#include<vector>
namespace SourceFiles {
	class Game : public Base::GameState
	{
	private:
		Base::PEPlatform* platform;
		Base::GameStateManager* manager;
		Base::ShaderManager* shaderManager;
		Graphics::Skybox* skybox;
		Player player;
		std::vector<Graphics::Model*> map;

		std::vector<SourceFiles::Enemy*> enemies;

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
		void LoadModels(const std::vector<std::string>& pathFileModels);
		void LoadEnemies(const std::vector<std::string>& pathFileModels);
	};
}

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