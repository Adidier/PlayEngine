include "Cylinder.h"
#include "Base/ResourceManager.h"

Cylinder::Cylinder()
{
	id = 103;
	model = (Graphic::Model*)ResourceManager::GetPtr()->GetElement("cylinder");
	transform.SetTranslation(2.0f, 200.0f, 2.0f);
	transform.SetScale(3.0f, 3.8f, 3.0f);
	rigidbody = new RigidBody(4, transform.GetTranslation(), 3.0f, 2.5f, this);
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