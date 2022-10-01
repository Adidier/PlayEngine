#include "Physics/Physics.h"
#include "btBulletDynamicsCommon.h"
#include "Base/GameObject.h"
#include "Base/ShaderManager.h"
#include "Base/PEPlatform.h"
#include <iostream>

Physics *Physics::ptr = nullptr;

void Physics::InitPhysics()
{
	///collision configuration contains default setup for memory, collision setup
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	//m_collisionConfiguration->setConvexConvexMultipointIterations();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	m_broadphase = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	m_solver = sol;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

	m_dynamicsWorld->setGravity(btVector3(0, -10, 0));

	gContactProcessedCallback = &Physics::callbackFunc;
}

glm::vec3 CreateRay() {
	Platform* platformPtr = Platform::GetPtr();
	float mouseX = platformPtr->mouseX / (platformPtr->GetWidth() * 0.5f) - 1.0f;
	float mouseY = platformPtr->mouseY / (platformPtr->GetHeight() * 0.5f) - 1.0f;
	//std::cout << mouseX<< "    "<< mouseY<<std::endl;

	glm::vec4 lRayStart_NDC(
		((float)platformPtr->mouseX / (float)platformPtr->GetWidth() - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
		((float)platformPtr->mouseY / (float)platformPtr->GetHeight() - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
		-1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
		1.0f
	);
	glm::vec4 lRayEnd_NDC(
		((float)platformPtr->mouseX / (float)platformPtr->GetWidth() - 0.5f) * 2.0f,
		((float)platformPtr->mouseY / (float)platformPtr->GetHeight() - 0.5f) * 2.0f,
		0.0,
		1.0f
	);

	ShaderManager* ptr = ShaderManager::GetPtr();
	glm::mat4 proj = ptr->GetProjectionMatrix();
	glm::mat4 view = ptr->GetViewMatrix();

	//glm::mat4 invVP = glm::inverse(proj * view);
	glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f);
//	std::cout << screenPos.x << "    " << screenPos.y << std::endl;
	//glm::vec4 worldPos = invVP * screenPos;
	//std::cout <<"** " << worldPos.x << "    " << worldPos.y << "    " << worldPos.z << "    " << worldPos.w<< std::endl;
	//glm::vec3 dir = glm::normalize(glm::vec3(worldPos));
	
	glm::mat4 M = glm::inverse(proj * view);
	glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
	glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;

	glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
	lRayDir_world = glm::normalize(lRayDir_world);

	return lRayDir_world;
}


void Physics::GetPickObject(glm::vec3 positionCamera) {
	glm::vec3 rayFrom = positionCamera;
	glm::vec3 rayTo = rayFrom+CreateRay()*1000.0f;
	btVector3 btRayFrom = btVector3(rayFrom.x, rayFrom.y, rayFrom.z);
	btVector3 btRayTo = btVector3(rayTo.x, rayTo.y, rayTo.z);

	btCollisionWorld::ClosestRayResultCallback rayCallback(btRayFrom, btRayTo);
	m_dynamicsWorld->rayTest(btRayFrom, btRayTo, rayCallback);

	if (rayCallback.hasHit())
	{
		auto a = static_cast<GameObject*>(static_cast<const btCollisionObject*>(rayCallback.m_collisionObject)->getUserPointer());
		if (a) {
			std::cout << "HIT" << a->id<<std::endl;
		}
	}
}

void Physics::Update(unsigned int delta)
{
	if (delta > 0)
	{
		m_dynamicsWorld->stepSimulation(1 / (float)delta); //TODO adidier
	}
}

btRigidBody* Physics::createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape, const btVector4& color)
{
	btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		shape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);

	btRigidBody* body = new btRigidBody(cInfo);



	body->setUserIndex(-1);
	m_dynamicsWorld->addRigidBody(body);
	return body;
}


Physics* Physics::GetPtr()
{
	if (ptr == nullptr)
	{
		ptr = new Physics();
	}
	return ptr;
}

bool Physics::callbackFunc(btManifoldPoint& cp, void* body0, void* body1) 
{
	auto ptr0 = static_cast<btCollisionObject*>(body0)->getUserPointer();
	auto ptr1 = static_cast<btCollisionObject*>(body1)->getUserPointer();
	auto obj0 = static_cast<GameObject*>(ptr0);
	auto obj1 = static_cast<GameObject*>(ptr1);
	if (obj0 && obj1)
	{
		obj0->OnTriggerEnter(ptr1);
		obj1->OnTriggerEnter(ptr0);
	}
	return false;
}