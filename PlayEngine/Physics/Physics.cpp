#include "Physics/Physics.h"
#include "btBulletDynamicsCommon.h"
#include "Base/GameObject.h"
#include "Base/PEPlatform.h"
#include "Base/ShaderManager.h"
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

bool Physics::RaycastScreen(int mouseScreenX, int mouseScreenY, glm::vec3 cameraPosition)
{
	glm::vec3 rayFrom = cameraPosition;
	glm::vec3 rayTo = cameraPosition + CreateRay(mouseScreenX, mouseScreenY)*100000.0f;

	auto btRayFrom = btVector3(rayFrom.x, rayFrom.y, rayFrom.z);
	auto btRayTo = btVector3(rayTo.x, rayTo.y, rayTo.z);
	btCollisionWorld::ClosestRayResultCallback ray(btRayFrom, btRayTo);
	m_dynamicsWorld->rayTest(btRayFrom, btRayTo, ray);
	if (ray.hasHit())
	{
		auto obj = (static_cast<const btCollisionObject*>(ray.m_collisionObject))->getUserPointer();
		if (obj) 
		{
			auto gameObject = static_cast<GameObject*>(obj);
			std::cout << "Hit with:" << gameObject->id << std::endl;
		}
	}
	return false;
}

glm::vec3 Physics::CreateRay(int mouseScreenX, int mouseScreenY)
{
	Platform* ptr = Platform::GetPtr();
	float mouseX = mouseScreenX / (ptr->GetWidth() * 0.5f) - 1;
	float mouseY = mouseScreenY / (ptr->GetHeight() * 0.5f) - 1;

	glm::vec4 startRay(mouseX, mouseY, -1, 1);
	glm::vec4 endRay(mouseX, mouseY, 0, 1);

	ShaderManager* ptrShaderManager = ShaderManager::GetPtr();
	glm::mat4 proj = ptrShaderManager->GetProjectionMatrix();
	glm::mat4 view = ptrShaderManager->GetViewMatrix();
	glm::mat4 impv = glm::inverse(proj * view);

	startRay = impv * startRay; startRay /= startRay.w;
	endRay = impv * endRay; endRay /= endRay.w;
	glm::vec3 rayWorld = endRay - startRay;
	return rayWorld;
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