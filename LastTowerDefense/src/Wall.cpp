#include "Wall.h"
#include "Base/ResourceManager.h"
#include "Physics/Physics.h"
#include "btBulletDynamicsCommon.h"
Wall::Wall() {
	wall = (Graphic::Model*)ResourceManager::GetPtr()->GetElement("wall");
	wall->AddTexture("brick");

	/*btBoxShape* colShape = new btBoxShape(btVector3(1000.1, 0.1, 1000.1));
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(
		btScalar(0.0),
		btScalar(-50.0),
		btScalar(0.0)));
	btQuaternion rot;
	rot.setEuler(0, 0, 0);
	startTransform.setRotation(rot);
	rigidBody = Physics::GetPtr()->createRigidBody(0.0f, startTransform, colShape);*/
}

void Wall::setTransform(float posx, float posy, float posz, float rotx) {

	/*btBoxShape* colShape = new btBoxShape(btVector3(1000.1, 0.1, 1000.1));
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(
		btScalar(posx),
		btScalar(posy),
		btScalar(posz)));
	btQuaternion rot;
	rot.setEuler(0, 0, 0);
	startTransform.setRotation(rot);
	rigidBody = Physics::GetPtr()->createRigidBody(0.0f, startTransform, colShape);
	xrot = rotx;
	*/
	
}

void Wall::Draw()
{
	wall->SetTransform(transform);
	wall->Draw();
}

void Wall::Update(unsigned int delta) {
	/*btVector3 pos = rigidBody->getWorldTransform().getOrigin();
	btQuaternion rot = rigidBody->getWorldTransform().getRotation();
	transform.SetTranslation(pos.getX(), pos.getY(), pos.getZ());
	glm::vec3 _rotation;
	rot.getEulerZYX(_rotation.x, _rotation.y, _rotation.z);
	_rotation.y = xrot;
	transform.SetRotation(_rotation.x, _rotation.y, _rotation.z);
	transform.SetScale(50, 10, 20);
	*/
}
