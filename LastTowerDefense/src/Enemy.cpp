#include "Enemy.h"
#include "Base/ResourceManager.h"
#include "Physics/Physics.h"


Enemy::Enemy(Player* player)
{
	this->player = player;
	scriptEnemy = new ScriptEnemy("Assets/AI/Enemy/Actions/Action.lua");

	model = (Graphic::Model *)ResourceManager::GetPtr()->GetElement("pina_pose");
	model->AddTexture("pina");
	transform.SetTranslation(0.0f, 0.0f, 0.0f);

	rigidBody = new RigidBody(1.0, glm::vec3(0, 0, 0), glm::vec3(2.5, 7.1, 3));
}

void Enemy::Draw()
{
	transform.SetScale(1.1f, 1.1f, 1.1f);
	model->SetTransform(transform);
	model->Draw();
}
 
void Enemy::Update(unsigned int delta)
{
	auto pos = rigidBody->GetObjectPosition();
	auto rot = rigidBody->GetObjectRotation();
	transform.SetTranslation(pos.x, pos.y, pos.z);
	transform.SetRotation(rot.x, rot.y, rot.z);
	glm::vec3 front(cos(rot.y), 0, sin(rot.y));
	float dot = glm::dot (front,player->GetCamera()->getCameraPosition());
	float normals = glm::length(front) * glm::length(player->GetCamera()->getCameraPosition());
	float angle = glm::acos(dot/normals);
	float distance = glm::distance(player->GetCamera()->getCameraPosition(), pos);
	
	//std::cout << distance << std::endl;
	auto action =scriptEnemy->GetAction(distance);
	if (action == "walk")
	{
		rigidBody->SetLinearVelocity(glm::vec3(200, 0, 0));
		rigidBody->ApplyForce(glm::vec3(200, 0, 0));
	}
}