#include "GameObject.h"
#include "Graphic/Model.h"
#include "Physics/RigidBody.h"

class Sphere : public GameObject
{
	private:
		RigidBody* rigidbody;
		Transform transform;
		Graphic::Model* model;
	public:
		Sphere();
		virtual ~Sphere();
		void Draw() override;
		void Update(unsigned int delta) override;
};