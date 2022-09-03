#include "Sphere.h"
#include "Base/ResourceManager.h"
#include "Physics/Physics.h"

Sphere::Sphere()
{
	model = (Graphic::Model*)ResourceManager::GetPtr()->GetElement("sphere");
	transform.SetTranslation(1.0f, 50.0f, 0.0f);
	transform.SetScale(1.0f, 1.0f, 1.0f);
	
	rigidBody = new RigidBody(0.6, transform.GetTranslation(), transform.GetScale().x);
}

void Sphere::Draw()
{
	model->SetTransform(transform);
	model->Draw();
}

void Sphere::Update(unsigned int delta)
{
	auto pos = rigidBody->GetObjectPosition();
	auto rot = rigidBody->GetObjectRotation();
	transform.SetTranslation(pos.x, pos.y, pos.z);
	transform.SetRotation(rot.x, rot.y, rot.z);
}