#pragma once
#include "GameObject.h"
#include "Graphic/Model.h"
#include "Physics/RigidBody.h"

class Level: public GameObject
{
private:
	Graphic::Model* container;
	Graphic::Model* robot;
	Transform Containertransform;
	Transform RobotTransform;
	btRigidBody* rigidBody;
	btRigidBody* rigidBodyrobot;
	float angle = 0;
public:
	Level();
	void Draw() override;
	void Update(unsigned int delta) override;

};

