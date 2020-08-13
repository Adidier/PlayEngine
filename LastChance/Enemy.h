#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Graphic/Model.h"
namespace SourceFiles 
{
	class Enemy : public SourceFiles::GameObject
	{
	private:
		Graphics::Model model;
		Base::Transform transform;
		Player* player;
	public:
		Enemy(Player* player, std::string path);
		void Draw() override;
		void Update() override;
	};
}

