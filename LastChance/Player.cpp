#include "Player.h"
namespace SourceFiles {
	Player::Player(std::string pathModel)
	{
		camera = Graphics::Camera(glm::vec3(10, 0.7, 0.6f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 55.0f, 0.1f);
		model.LoadModel("Assets/Models/player.obj");
	}

	Graphics::Camera* Player::GetCamera()
	{
		return &camera;
	}

	std::vector<glm::vec4> Player::GetBoundingBox()
	{
		auto position = camera.getCameraPosition();
		transform.SetTranslation(position.x, position.y, position.z);
		auto rotacion = camera.getCameraRotation();
		transform.SetRotation(0, 0, 0);
		transform.SetScale(1, 1, 1);
		return model.GetMesh()->UpdateBoundingBox(transform.GetTransform());
	}
}