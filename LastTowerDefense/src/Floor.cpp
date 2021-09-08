#include "Floor.h"
#include "Base/ResourceManager.h"
#include "Physics/Physics.h"
#include "btBulletDynamicsCommon.h"

Floor::Floor()
{	
	model = dynamic_cast<Graphic::Model*>(ResourceManager::GetPtr()->GetElement("floor"));
	model->AddTexture("brick");
	glm::vec3 cornerModel = model->GetCorner();

	btBoxShape* colShape = new btBoxShape(btVector3(650, 0, 650));
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(
		btScalar(0.0),
		btScalar(0.0),
		btScalar(0.0)));
	btQuaternion rot;
	rot.setEuler(0, 0, 0);
	startTransform.setRotation(rot);
	rigidBody = Physics::GetPtr()->createRigidBody(0.0f, startTransform, colShape);	
}

void Floor::Draw()
{
	model->SetTransform(transform);
	model->Draw();
}

void Floor::Update(unsigned int delta)
{

	btVector3 pos = rigidBody->getWorldTransform().getOrigin();
	btQuaternion rot = rigidBody->getWorldTransform().getRotation();
	transform.SetTranslation(pos.getX(), pos.getY(), pos.getZ());
	glm::vec3 _rotation;
	rot.getEulerZYX(_rotation.z, _rotation.y, _rotation.x);
	transform.SetRotation(_rotation.x, _rotation.y, _rotation.z);
	transform.SetScale(1, 1, 1);
}