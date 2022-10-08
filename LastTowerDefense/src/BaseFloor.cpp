#include "BaseFloor.h"
#include "Base/ResourceManager.h"
#include "Physics/Physics.h"
#include "btBulletDynamicsCommon.h"

BaseFloor::BaseFloor()
{	
	model = dynamic_cast<Graphic::Model*>(ResourceManager::GetPtr()->GetElement("cube"));
	model->AddTexture("brick2");
	glm::vec3 cornerModel = model->GetCorner();
	btBoxShape* colShape = new btBoxShape(btVector3(8, 4, 3));
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(
		btScalar(0.0),
		btScalar(2.0),
		btScalar(0.0)));
	btQuaternion rot;
	rot.setEuler(0, 0, 0);
	startTransform.setRotation(rot);
	rigidBody = Physics::GetPtr()->createRigidBody(0.0f, startTransform, colShape);	
	transform.SetTranslation(0, 2, 0);
	transform.SetRotation(0, 0, 0);
	transform.SetScale(8, 4, 3);
}

void BaseFloor::Draw()
{
	model->SetTransform(transform);
	model->Draw();
}

void BaseFloor::Update(unsigned int delta)
{
}

void BaseFloor::OnTriggerEnter(void* ptr)
{

}