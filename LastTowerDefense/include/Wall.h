#pragma once
#include "Base/GameObject.h"
#include "Graphic/Model.h"
#include "Physics/RigidBody.h"
class Wall: public GameObject
{
private:
	Graphic::Model* wall;
	Transform transform;
	btRigidBody* rigidBody;
	float angle = 0;
	float xrot = 0;
public:
	Wall();
	void setTransform(float posx, float posy, float posz, float rotx);
	void Draw() override;
	void Update(unsigned int delta) override;

};

