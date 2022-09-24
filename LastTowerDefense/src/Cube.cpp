#include "Cube.h"
#include "Base/ResourceManager.h"

Cube::Cube()
{
	id = 101;
	model = (Graphic::Model*)ResourceManager::GetPtr()->GetElement("cube");
	transform.SetTranslation(0.0f, 200.0f, 0.0f);
	transform.SetScale(2.0f, 2.0f, 2.0f);
	rigidbody = new RigidBody(0.6, transform.GetTranslation(), transform.GetScale(),this);
}

Cube::~Cube()
{
	//TODO 
}

void Cube::Draw()
{
	model->SetTransform(transform);
	model->Draw();
}

void Cube::Update(unsigned int delta)
{
	transform.SetTranslation(rigidbody->GetObjectPosition());
	transform.SetRotation(rigidbody->GetObjectRotation());
}

void Cube::OnTriggerEnter(void *ptr)
{
	auto obj0 = static_cast<GameObject*>(ptr);

	std::cout << "hit cube";
}