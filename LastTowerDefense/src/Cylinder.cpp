#include "Cylinder.h"
#include "Base/ResourceManager.h"

Cylinder::Cylinder()
{
	id = 103;
	model = (Graphic::Model*)ResourceManager::GetPtr()->GetElement("cylinder");
	transform.SetTranslation(10.0f, 200.0f, 0.0f);
	transform.SetScale(2.0f, 2.0f, 2.0f);
	rigidbody = new RigidBody(2.0f, transform.GetTranslation(), 4.0f, 4.0f, 4.0f, this);
}

Cylinder::~Cylinder()
{
	//TODO 
}

void Cylinder::Draw()
{
	model->SetTransform(transform);
	model->Draw();
}

void Cylinder::Update(unsigned int delta)
{
	transform.SetTranslation(rigidbody->GetObjectPosition());
	transform.SetRotation(rigidbody->GetObjectRotation());
}

void Cylinder::OnTriggerEnter(void* ptr)
{
	auto obj0 = static_cast<GameObject*>(ptr);

	std::cout << "hit cylinder";
}