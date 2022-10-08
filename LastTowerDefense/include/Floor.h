#pragma once
#include "Base/GameObject.h"
#include "Player.h"
#include "Graphic/Model.h"
#include "btBulletDynamicsCommon.h"
#include "Bullet3Common\b3Transform.h"
#include <list>
#include "Cube.h"

class Floor : public GameObject
{
private:
	Graphic::Model* model;
	Transform transform;
	btRigidBody* rigidBody;
	float angle = 0;
	std::list<Cube*>* boxes;
public:
	Floor(std::list<Cube*> *_boxes);
	void Draw() override;
	void Update(unsigned int delta) override;
	void OnTriggerEnter(void *ptr) override;
};

