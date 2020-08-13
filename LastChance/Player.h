#pragma once
#include "Graphic/Camera.h"
#include "Graphic/Model.h"
namespace SourceFiles {
	class Player
	{
	private:
		Graphics::Camera camera;
		Graphics::Model model;
		Base::Transform transform;
	private:
		int energy{ 0 };
	public:
		Player(std::string pathModel);
		Graphics::Camera* GetCamera();
		std::vector<glm::vec4> GetBoundingBox();
	};
}

