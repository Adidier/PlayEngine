#include "Enemy.h"
#include "Base/ResourceManager.h"
#include "Physics/Physics.h"


Enemy::Enemy(Player* player)
{
	this->player = player;
	scriptEnemy = new ScriptEnemy("Assets/Scripts/Enemy/AI.lua");

	model = (Model *)ResourceManager::GetPtr()->GetElement("Enemy", "Assets/Models/pina_pose.obj");
	model->AddTexture("Assets/Textures/pina.png");
	transform.SetTranslation(0.0f, 0.0f, 0.0f);

	rigidBody = new RigidBody(0.1, glm::vec3(0, 0, 0), glm::vec3(2.1, 2.1, 2.1));
}

void Enemy::Draw()
{
	transform.SetScale(1.1f, 1.1f, 1.1f);
	//transform.SetRotation(0, 0, 0);
	model->SetTransform(transform);
	model->Draw();
}

void Enemy::Update(unsigned int delta)
{
	/*glm::vec3 dir = player->GetCamera()->getCameraPosition() - transform.GetTranslation();
	dir = glm::normalize(dir)*0.1f;
	transform.SetTranslation(transform.GetTranslation().x + dir.x,
		transform.GetTranslation().y + dir.y,
		transform.GetTranslation().z + dir.z);
		*/

	//transform.SetTranslation()
	auto pos = rigidBody->GetObjectPosition();
	auto rot = rigidBody->GetObjectRotation();
	transform.SetTranslation(pos.x, pos.y, pos.z);
	transform.SetRotation(rot.x, rot.y, rot.z);
}