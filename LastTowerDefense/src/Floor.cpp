#include "Floor.h"
#include "Base/ResourceManager.h"
#include "Physics/Physics.h"
#include "btBulletDynamicsCommon.h"
#include "Physics/Physics.h"

Floor::Floor(std::list<Cube*> *_boxes)
{	
	id = 1;
	boxes = _boxes;
	model = dynamic_cast<Graphic::Model*>(ResourceManager::GetPtr()->GetElement("floor"));
	model->AddTexture("brick2");
	glm::vec3 cornerModel = model->GetCorner();
	btBoxShape* colShape = new btBoxShape(btVector3(1000, 0, 1000));
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(
		btScalar(0.0),
		btScalar(0.0),
		btScalar(0.0)));
	btQuaternion rot;
	rot.setEuler(0, 0, 0);
	startTransform.setRotation(rot);
	rigidBody = Physics::GetPtr()->createRigidBody(0.0f, startTransform, colShape);	
	transform.SetTranslation(0, 0, 0);
	transform.SetRotation(0, 0, 0);
	transform.SetScale(1, .1, 1);
	rigidBody->setUserPointer(this);
}

void Floor::Draw()
{
	model->SetTransform(transform);
	model->Draw();
}

void Floor::Update(unsigned int delta)
{
}

void Floor::OnTriggerEnter(void* ptr)
{
	auto obj0 = static_cast<GameObject*>(ptr);
	Cube* badCube = nullptr;
	for (auto box :*boxes) {
		if (box->id == obj0->id) {
			badCube = box;
			std::cout << "hit cube";
			break;
		}
	}
	if (badCube) {
		auto cube = static_cast<Cube*>(badCube);
		Physics::GetPtr()->RemoveRigidBody(cube->rigidbody->rigidBody);
		boxes->remove(badCube);
	}
}