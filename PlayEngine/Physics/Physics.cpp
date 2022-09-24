#include "Physics/Physics.h"
#include "btBulletDynamicsCommon.h"
#include "Base/GameObject.h"
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