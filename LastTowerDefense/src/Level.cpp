#include "Level.h"
#include "Base/ResourceManager.h"
#include "Physics/Physics.h"
#include "btBulletDynamicsCommon.h"

Level::Level() {
	//container = (Graphic::Model*)ResourceManager::GetPtr()->GetElement("container");
	//container->AddTexture("ContainerAlbedo");

	//btBoxShape* colShape = new btBoxShape(btVector3(1000.1, 0.1, 1000.1));
	//btTransform startTransform;
	//startTransform.setIdentity();
	//startTransform.setOrigin(btVector3(
	//	btScalar(200.0),
	//	btScalar(-50.0),
	//	btScalar(0.0)));
	//btQuaternion rot;
	//rot.setEuler(180, 0, 0);
	//startTransform.setRotation(rot);
	//rigidBody = Physics::GetPtr()->createRigidBody(0.0f, startTransform, colShape);
}

void Level::Draw()
{
	//container->SetTransform(Containertransform);
	//container->Draw();
}

void Level::Update(unsigned int delta) {
	//btVector3 pos = rigidBody->getWorldTransform().getOrigin();
	//btQuaternion rot = rigidBody->getWorldTransform().getRotation();
	//Containertransform.SetTranslation(pos.getX(), pos.getY(), pos.getZ());
	//glm::vec3 _rotation;
	//rot.getEulerZYX(_rotation.x, _rotation.y, _rotation.z);
	//Containertransform.SetRotation(_rotation.x, _rotation.y, _rotation.z);
	//Containertransform.SetScale(20, 20, 20);
}
