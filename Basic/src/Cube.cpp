#include "Cube.h"
#include "Base/ResourceManager.h"

Cube::Cube(long long _id,float mass) : rigidbody(nullptr)
{
	id = _id;
	dir = rand() % 10 > 5 ? 1 : -1;
	model = (Graphic::Model*)ResourceManager::GetPtr()->GetElement("pina_pose");
	model->AddTexture("pina");
	transform.SetTranslation(0.0f, 100.0f, 0.0f);
	transform.SetScale(8.0f, 4.0f, 3.0f);
	InitRigidBody(mass);
}

void Cube::InitRigidBody(float mass) 
{
	if (mass > 0 && !rigidbody)
	{
		rigidbody = new RigidBody(mass, transform.GetTranslation(), transform.GetScale(), this);
	}
}

Cube::~Cube()
{
	delete rigidbody;
	delete model;
}

void Cube::Draw()
{
	model->SetTransform(transform);
	model->Draw();
}

void Cube::Update(unsigned int delta)
{
	if (rigidbody) {
		transform.SetTranslation(rigidbody->GetObjectPosition());
		transform.SetRotation(rigidbody->GetObjectRotation());
	}
	else {
		auto position = transform.GetTranslation();
		position += glm::vec3(0.1, 0, 0) * dir ;
		if ( position.x >70 || position.x < -70) {
			dir *= -1;
		}
		transform.SetTranslation(position);
	}
}

void Cube::OnTriggerEnter(void *ptr)
{
	auto obj0 = static_cast<GameObject*>(ptr);

	std::cout << "hit cube";
}