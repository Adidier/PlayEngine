#pragma once
#include "../Export.h"
#include <glm.hpp>
#include "btBulletDynamicsCommon.h"
#include "Bullet3Common\b3Transform.h"

class PLAYENGINE RigidBody
{
public:
	RigidBody(const float &mass,const glm::vec3 &pos, const glm::vec3 &box);
	RigidBody(const float& mass, const glm::vec3& pos, const float radio);

	glm::vec3 GetObjectPosition();
	glm::vec3 GetObjectRotation();
	void ApplyForce(const glm::vec3& rForce);
	void SetLinearVelocity(const glm::vec3& velocity);

private:
	btRigidBody* rigidBody;
};