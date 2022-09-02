#include "Enemy.h"
#include "Base/ResourceManager.h"
#include "Physics/Physics.h"


Enemy::Enemy(Player* player)
{
	this->player = player;
	scriptEnemy = new ScriptEnemy("../../Resources/Assets/AI/Enemy/Actions/Action.lua");

	model = (Graphic::Model *)ResourceManager::GetPtr()->GetElement("pina_pose");
	model->AddTexture("pina");
	model->AddTexture("pina_normal");
	transform.SetTranslation(0.0f, 0.0f, 0.0f);
	glm::vec3 cornerModel = model->GetCorner();
	rigidBody = new RigidBody(0.6, glm::vec3(rand()%10, 50+rand() % 90, 0), glm::vec3(5, 5, 5));
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
	if (distance<50)
	{
		rigidBody->SetLinearVelocity(glm::vec3(0, 0, 0));
		rigidBody->ApplyForce(glm::vec3(rand()%50, rand() % 50, rand() % 50));
	}
}