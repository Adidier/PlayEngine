#include "Player.h"
#include "Base/ResourceManager.h"

Player::Player() 
{
	camera = Camera(glm::vec3(0, 40, -100), glm::vec3(0.0f, -1.0f, 0.0f), 990.0f, -5.0f, 0.0f, 0.0f);
}

Camera *Player::GetCamera()
{
	return &camera;
}
