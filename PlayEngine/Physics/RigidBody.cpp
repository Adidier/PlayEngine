#include "Physics/RigidBody.h"
#include "Physics/Physics.h"

RigidBody::RigidBody(const float& mass, const glm::vec3& pos, const glm::vec3& box)
{
	btBoxShape* colShape = new btBoxShape(btVector3(box.x, box.y, box.z));
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	rigidBody = Physics::GetPtr()->createRigidBody(mass, startTransform, colShape);
	rigidBody->setRollingFriction(0);
}

RigidBody::RigidBody(const float& mass, const glm::vec3& pos, float ratio)
{
	btSphereShape* colShape = new btSphereShape(ratio);
	btTransform startTransform;
	btVector3 localInertia(0, -10, 0);
	colShape->calculateLocalInertia(mass, localInertia);
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	rigidBody = Physics::GetPtr()->createRigidBody(mass, startTransform, colShape);
//	rigidBody->setRollingFriction(1000);
}


RigidBody::RigidBody(const float& mass, const glm::vec3& pos,float w, float h, float ratio)
{
	btVector3 size(w, h, h);
	btCylinderShape* colShape = new btCylinderShape(size);
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	rigidBody = Physics::GetPtr()->createRigidBody(mass, startTransform, colShape);
	rigidBody->setRollingFriction(0);

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