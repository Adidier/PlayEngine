#pragma once
#include "Graphic/Camera.h"
#include "Graphic/Model.h"
class Player
{
	private:
		Camera camera;
		Model *model;
		Transform transform;
	private:
		int energy { 0 };
	public:
		Player();
		Camera *GetCamera();
		std::vector<glm::vec4> GetBoundingBox();
};

