#pragma once
#include "Graphic/Camera.h"
#include "Graphic/Model.h"
#include "btBulletDynamicsCommon.h"

class Player
{
	private:
		Camera camera;
		Transform transform;
		btRigidBody* rigidBody;
	private:
		int energy { 0 };
	public:
		Player();
		Camera *GetCamera();
};

