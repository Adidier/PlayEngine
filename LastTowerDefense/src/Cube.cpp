#include "Cube.h"
#include "Base/ResourceManager.h"
#include "Physics/Physics.h"

Cube::Cube()
{
	model = (Graphic::Model*)ResourceManager::GetPtr()->GetElement("cube");
	transform.SetTranslation(0.0f, 200.0f, 0.0f);
	transform.SetScale(1.0f, 2.0f, 1.0f);	
	rigidBody = new RigidBody(0.6, transform.GetTranslation(), transform.GetScale());
}

void Cube::Draw()
{
	model->SetTransform(transform);
	model->Draw();
}

void Cube::Update(unsigned int delta)
{
	auto pos = rigidBody->GetObjectPosition();
	auto rot = rigidBody->GetObjectRotation();
	transform.SetTranslation(pos.x, pos.y, pos.z);
	transform.SetRotation(rot.x, rot.y, rot.z);
}