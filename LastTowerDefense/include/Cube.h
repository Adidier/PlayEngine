#include "GameObject.h"
#include "Graphic/Model.h"
#include "Physics/RigidBody.h"

class Cube : public GameObject
{
private:
	RigidBody* rigidbody;
	Transform transform;
	Graphic::Model* model;
public:
	Cube();
	virtual ~Cube();
	void Draw() override;
	void Update(unsigned int delta) override;
};