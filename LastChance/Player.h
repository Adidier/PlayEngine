#pragma once
#include "Graphic/Camera.h"
#include "Graphic/Model.h"
class Player
{
	private:
		Camera camera;
		Model model;
		Transform transform;
	private:
		int energy { 0 };
	public:
		Player(std::string pathModel);
		Camera *GetCamera();
		std::vector<glm::vec4> GetBoundingBox();
};

