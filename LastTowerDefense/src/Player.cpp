#include "Player.h"
#include "Base/ResourceManager.h"

Player::Player() 
{
	camera = Camera(glm::vec3(10, 10.7, 100.6f), glm::vec3(0.0f, -1.0f, 0.0f), 0.0f, 0.0f, 355.0f, 0.1f);
	model = (Graphic::Model*)ResourceManager::GetPtr()->GetElement("pina_pose");
}

Camera *Player::GetCamera()
{
	return &camera;
}
