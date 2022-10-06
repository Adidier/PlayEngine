#pragma once
#include "../Export.h"
#include <glm.hpp>
#include "btBulletDynamicsCommon.h"
#include "Bullet3Common\b3Transform.h"
#include "Base/GameObject.h"

class PLAYENGINE RigidBody
{
public:
	RigidBody(const float &mass,const glm::vec3 &pos, const glm::vec3 &box, GameObject* obj);
	RigidBody(const float& mass, const glm::vec3& pos, const float radio, GameObject* obj);
	RigidBody(const float& mass, const glm::vec3& pos, const float radio1, const float height, const float radio2, GameObject* obj);

	glm::vec3 GetObjectPosition();
	glm::vec3 GetObjectRotation();
	void ApplyForce(const glm::vec3& rForce);
	void SetLinearVelocity(const glm::vec3& velocity);
	int a;
private:
	btRigidBody* rigidBody;
};