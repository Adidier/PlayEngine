#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Graphic/Model.h"
class Enemy : public GameObject
{
private:
	Model model;
	Transform transform;
	Player* player;
public:
	Enemy(Player* player, std::string path);
	void Draw() override;
	void Update() override;
};

