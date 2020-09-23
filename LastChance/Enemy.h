#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Graphic/Model.h"
#include "Physics/RigidBody.h"
#include "ScriptEnemy.h"

class Enemy : public GameObject
{
private:
	ScriptEnemy* scriptEnemy;
	Model* model;
	Transform transform;
	Player* player;
	RigidBody* rigidBody;
public:
	Enemy(Player* player);
	void Draw() override;
	void Update(unsigned int delta) override; 
};


