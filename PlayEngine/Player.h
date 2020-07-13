#pragma once
#include "CGE/Graphic/Camera.h"
#include "CGE/Graphic/Model.h"
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

