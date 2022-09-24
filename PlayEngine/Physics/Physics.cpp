#include "Physics/Physics.h"
#include "Physics/RigidBody.h"
#include <map>
#include "btBulletDynamicsCommon.h"
#include "../include/Base/ShaderManager.h"
#include "../include/Base/PEPlatform.h"

Physics *Physics::ptr = nullptr;
std::map<const btCollisionObject*, std::vector<btManifoldPoint*>> objectsCollisions;


void myTickCallback(btDynamicsWorld* dynamicsWorld, btScalar timeStep) {
	objectsCollisions.clear();
	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++) {
		btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		auto* objA = contactManifold->getBody0();
		auto* objB = contactManifold->getBody1();
		auto& collisionsA = objectsCollisions[objA];
		auto& collisionsB = objectsCollisions[objB];
		int numContacts = contactManifold->getNumContacts();
		for (int j = 0; j < numContacts; j++) {
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			collisionsA.push_back(&pt);
			collisionsB.push_back(&pt);
		}
	}
}

bool callbackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	const btCollisionObject*object1 = colObj0Wrap->getCollisionObject();
	const btCollisionObject* object2 = colObj0Wrap->getCollisionObject();

	return true;
}

bool MyContactProcessedCallback(btManifoldPoint& cp, void* body0, void* body1)
{
	auto a = static_cast<RigidBody*>(static_cast<btCollisionObject*>(body0)->getUserPointer());
	auto b = static_cast<RigidBody*>(static_cast<btCollisionObject*>(body1)->getUserPointer());
	//printf("processed\n");
	if (a && b) {
		a->GetObjectPosition();
		return true;
	}
	return false;
}



void Physics::InitPhysics()
{
	///collision configuration contains default setup for memory, collision setup
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	//m_collisionConfiguration->setConvexConvexMultipointIterations();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	m_broadphase = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	m_solver = new btSequentialImpulseConstraintSolver;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

	m_dynamicsWorld->setGravity(btVector3(0, -10, 0));

	//m_dynamicsWorld->setInternalTickCallback(myTickCallback);
	//gContactAddedCallback = &callbackFunc;
	gContactProcessedCallback = &MyContactProcessedCallback;

}


glm::vec3 CreateRay() {
	Platform* platformPtr = Platform::GetPtr();
	float mouseX = platformPtr->mouseX / (platformPtr->GetWidth() * 0.5f) - 1.0f;
	float mouseY = platformPtr->mouseY / (platformPtr->GetHeight() * 0.5f) - 1.0f;
	//std::cout << mouseX<< "    "<< mouseY<<std::endl;

	ShaderManager* ptr = ShaderManager::GetPtr();
	glm::mat4 proj = ptr->GetProjectionMatrix();
	glm::mat4 view = ptr->GetViewMatrix();

	glm::mat4 invVP = glm::inverse(proj * view);
	glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f);
	//std::cout << screenPos.x << "    " << screenPos.y << std::endl;
	glm::vec4 worldPos = invVP * screenPos;

	//glm::vec3 dir = glm::normalize(glm::vec3(worldPos));

	return worldPos;
}

void Physics::GetPickObject(glm::vec3 positionCamera) {
	glm::vec3 rayFrom = positionCamera;
	glm::vec3 rayTo = CreateRay();
	btVector3 btRayFrom = btVector3(rayFrom.x, rayFrom.y, rayFrom.z);
	btVector3 btRayTo = btVector3(rayTo.x, rayTo.y, rayTo.z);

	btCollisionWorld::ClosestRayResultCallback rayCallback(btRayFrom, btRayTo);
	m_dynamicsWorld->rayTest(btRayFrom, btRayTo, rayCallback);

	if (rayCallback.hasHit())
	{
		auto a = static_cast<RigidBody*>(static_cast<const btCollisionObject*>(rayCallback.m_collisionObject)->getUserPointer());
		if (a) {
			a->GetObjectPosition();
			std::cout << "HIT" << std::endl;
		}
	}
}



void Physics::Update(unsigned int delta)
{
	if (delta > 0)
	{
		m_dynamicsWorld->stepSimulation(delta); //TODO adidier
		btVector3 direction(1,0,0);
		btVector3 cam(0,0,0);
		btCollisionWorld::AllHitsRayResultCallback rayCallback(cam,direction);
		m_dynamicsWorld->rayTest(cam, direction, rayCallback);
		if (rayCallback.hasHit())
		{
			for (int i = 0; i < rayCallback.m_collisionObjects.size(); i++)
			{

				auto a = static_cast<RigidBody*>(static_cast<const btCollisionObject*>(rayCallback.m_collisionObjects[i])->getUserPointer());
				if (a) {
					a->GetObjectPosition();
				}
			}
		}
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
	//body->setContactProcessingThreshold(m_defaultContactProcessingThreshold);

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