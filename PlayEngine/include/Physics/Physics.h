#pragma once
#include "../Export.h"
#include <GL\glew.h>
#include <vector>
#include "glm.hpp"
#include "BulletCollision/CollisionDispatch/btCollisionObject.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "examples/CommonGUIHelperInterface.h"
#include "LinearMath/btTransform.h"
#include "LinearMath/btHashMap.h"

static bool callbackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1);

class PLAYENGINE Physics
{
private:
	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
	btBroadphaseInterface* m_broadphase;
	btCollisionDispatcher* m_dispatcher;
	btConstraintSolver* m_solver;
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btDiscreteDynamicsWorld* m_dynamicsWorld;
	GUIHelperInterface* m_guiHelper;
	static Physics* ptr;
public:
	static Physics* GetPtr();
	void InitPhysics();
	btRigidBody* createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape, const btVector4& color = btVector4(1, 0, 0, 1));
	

	void Update(unsigned int delta);
	void GetPickObject(glm::vec3 positionCamera);
private:
	Physics() {};

};
