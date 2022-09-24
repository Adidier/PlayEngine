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
	static bool callbackFunc(btManifoldPoint& cp, void* body0, void* body1);
	void Update(unsigned int delta);
private:
	Physics() {};
};