#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Graphic/Model.h"
#include "Physics/RigidBody.h"

class Enemy : public GameObject
{
private:
	Model* model;
	Transform transform;
	Player* player;
	RigidBody* rigidBody;
public:
	Enemy(Player* player);
	void Draw() override;
	void Update() override;
};

