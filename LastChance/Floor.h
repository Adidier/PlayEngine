#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Graphic/Model.h"
#include "btBulletDynamicsCommon.h"
#include "Bullet3Common\b3Transform.h"

class Floor : public GameObject
{
private:
	Model* model;
	Transform transform;
	btRigidBody* rigidBody;
	float angle = 0;
public:
	Floor();
	void Draw() override;
	void Update() override;
};

