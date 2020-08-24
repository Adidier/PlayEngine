#include "Enemy.h"
#include "Base/ResourceManager.h"
#include "Physics/Physics.h"
#include "btBulletDynamicsCommon.h"

Enemy::Enemy(Player* player)
{
	this->player = player;
	auto resourceManger = ResourceManager::GetPtr();
	resourceManger->Add(ResourceType::Model3d, "Enemy", "Assets/Models/pina_pose.obj");
	model = (Model *)ResourceManager::GetPtr()->GetElement("Enemy", "Assets/Models/pina_pose.obj");
	model->AddTexture("Assets/Textures/pina.png");
	transform.SetTranslation(0.0f, 0.0f, 0.0f);


	btBoxShape* colShape = new btBoxShape(btVector3(2.1, 2.1, 2.1));
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(
		btScalar(0.0),
		btScalar(0.0),
		btScalar(0.0)));
	rigidBody = Physics::GetPtr()->createRigidBody(0.1f, startTransform, colShape);
	
}

void Enemy::Draw()
{
	transform.SetScale(1.1f, 1.1f, 1.1f);
	//transform.SetRotation(0, 0, 0);
	model->SetTransform(transform);
	model->Draw();
}

void Enemy::Update()
{
	/*glm::vec3 dir = player->GetCamera()->getCameraPosition() - transform.GetTranslation();
	dir = glm::normalize(dir)*0.1f;
	transform.SetTranslation(transform.GetTranslation().x + dir.x,
		transform.GetTranslation().y + dir.y,
		transform.GetTranslation().z + dir.z);
		*/

	//transform.SetTranslation()
	btVector3 pos = rigidBody->getWorldTransform().getOrigin();
	btQuaternion rot = rigidBody->getWorldTransform().getRotation();
	transform.SetTranslation(pos.getX(), pos.getY(), pos.getZ());
	glm::vec3 _rotation;
	rot.getEulerZYX(_rotation.x, _rotation.y, _rotation.z);
	transform.SetRotation(_rotation.x, _rotation.y, _rotation.z);
}