#include "Physics/RigidBody.h"
#include "Physics/Physics.h"

RigidBody::RigidBody(const float& mass, const glm::vec3& pos, const glm::vec3& box, GameObject* obj)
{
	btBoxShape* colShape = new btBoxShape(btVector3(box.x, box.y, box.z));//TODO arreglar tamanio de la caja de colision
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	rigidBody = Physics::GetPtr()->createRigidBody(mass, startTransform, colShape);
	rigidBody->setRollingFriction(0);
	rigidBody->setUserPointer(obj);
}

RigidBody::RigidBody(const float& mass, const glm::vec3& pos, const float radio, GameObject* obj)
{
	btSphereShape* colShape = new btSphereShape(radio);//TODO arreglar tamanio de la caja de colision
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	rigidBody = Physics::GetPtr()->createRigidBody(mass, startTransform, colShape);
	rigidBody->setRollingFriction(0);
	rigidBody->setUserPointer(obj);
}

RigidBody::RigidBody(const float& mass, const glm::vec3& pos, const float height, const float radio1, const float radio2,  GameObject* obj)
{
	btCylinderShape* colShape = new btCylinderShape(radio1, height, radio2 );//TODO arreglar tamanio de la caja de colision
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	rigidBody = Physics::GetPtr()->createRigidBody(mass, startTransform, colShape);
	rigidBody->setRollingFriction(0);
	rigidBody->setUserPointer(obj);
}

glm::vec3 RigidBody::GetObjectPosition()
{
	auto pos = rigidBody->getWorldTransform().getOrigin();
	return glm::vec3(pos.getX(), pos.getY(), pos.getZ());
}

glm::vec3 RigidBody::GetObjectRotation()
{
	auto rot = rigidBody->getWorldTransform().getRotation();
	float x, y, z;
	rot.getEulerZYX(z, y, x);
	return glm::vec3(x, y, z);
}

void RigidBody::ApplyForce(const glm::vec3& rForce)
{
	rigidBody->applyCentralForce(btVector3(rForce.x, rForce.y, rForce.z));
}

void RigidBody::SetLinearVelocity(const glm::vec3& velocity)
{
	rigidBody->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
}