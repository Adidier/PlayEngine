#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Graphic/Model.h"
#include "btBulletDynamicsCommon.h"
#include "Bullet3Common\b3Transform.h"

class Enemy : public GameObject
{
private:
	Model* model;
	Transform transform;
	Player* player;
	btRigidBody* rigidBody;
public:
	Enemy(Player* player);
	void Draw() override;
	void Update() override;
};

