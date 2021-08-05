#pragma once
#include "Graphic/Camera.h"
#include "Graphic/Model.h"
#include "btBulletDynamicsCommon.h"

class Player
{
	private:
		Camera camera;
		Graphic::Model *model;
		Transform transform;
		btRigidBody* rigidBody;
	private:
		int energy { 0 };
	public:
		Player();
		Camera *GetCamera();
		//adidier std::vector<glm::vec4> GetBoundingBox();
};

