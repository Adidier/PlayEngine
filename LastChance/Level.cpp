#include "Level.h"
#include "Base/ResourceManager.h"
#include "Physics/Physics.h"
#include "btBulletDynamicsCommon.h"

Level::Level() {
	container = (Model*)ResourceManager::GetPtr()->GetElement("Container", "Assets/Models/Container.obj");
	container->AddTexture("Assets/Textures/ContainerAlbedo.png");

	//robot = (Model*)ResourceManager::GetPtr()->GetElement("Robot", "Assets/Models/robot.obj");
	//robot->AddTexture("Assets/Textures/RobbiDiffuse.png");

	btBoxShape* colShape = new btBoxShape(btVector3(1000.1, 0.1, 1000.1));
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(
		btScalar(200.0),
		btScalar(-50.0),
		btScalar(0.0)));
	btQuaternion rot;
	rot.setEuler(180, 0, 0);
	startTransform.setRotation(rot);
	rigidBody = Physics::GetPtr()->createRigidBody(0.0f, startTransform, colShape);

	/*btBoxShape* colShape2 = new btBoxShape(btVector3(1000.1, 0.1, 1000.1));
	btTransform startTransform2;
	startTransform2.setIdentity();
	startTransform2.setOrigin(btVector3(
		btScalar(0.0),
		btScalar(-50.0),
		btScalar(0.0)));
	btQuaternion rot2;
	rot2.setEuler(0, 0, 0);
	startTransform2.setRotation(rot2);
	rigidBodyrobot = Physics::GetPtr()->createRigidBody(0.0f, startTransform2, colShape2);*/
}

void Level::Draw()
{
	container->SetTransform(Containertransform);
	container->Draw();

	/*robot->SetTransform(RobotTransform);
	robot->Draw();*/
}

void Level::Update(unsigned int delta) {
	btVector3 pos = rigidBody->getWorldTransform().getOrigin();
	btQuaternion rot = rigidBody->getWorldTransform().getRotation();
	Containertransform.SetTranslation(pos.getX(), pos.getY(), pos.getZ());
	glm::vec3 _rotation;
	rot.getEulerZYX(_rotation.x, _rotation.y, _rotation.z);
	Containertransform.SetRotation(_rotation.x, _rotation.y, _rotation.z);
	Containertransform.SetScale(20, 20, 20);

	/*btVector3 pos2 = rigidBodyrobot->getWorldTransform().getOrigin();
	btQuaternion rot2 = rigidBodyrobot->getWorldTransform().getRotation();
	RobotTransform.SetTranslation(pos2.getX(), pos2.getY(), pos2.getZ());
	glm::vec3 _rotation2;
	rot2.getEulerZYX(_rotation2.x, _rotation2.y, _rotation2.z);
	RobotTransform.SetRotation(_rotation2.x, _rotation2.y, _rotation2.z);
	RobotTransform.SetScale(20, 20, 20);*/
}
