#include "Physics/RigidBody.h"
#include "Physics/Physics.h"


RigidBody::RigidBody(const float& mass, const glm::vec3& pos, const glm::vec3& box)
{
	btBoxShape* colShape = new btBoxShape(btVector3(box.x, box.y, box.z));
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	rigidBody = Physics::GetPtr()->createRigidBody(mass, startTransform, colShape);
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