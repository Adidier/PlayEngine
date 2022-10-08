#include "Base/GameObject.h"
#include "Graphic/Model.h"
#include "Physics/RigidBody.h"

class Cube : public GameObject
{
private:
	RigidBody* rigidbody;
	Transform transform;
	Graphic::Model* model;
	float dir;
public:
	Cube(float mass = 1);
	virtual ~Cube();
	void Draw() override;
	void Update(unsigned int delta) override;
	void OnTriggerEnter(void *ptr) override;
	void InitRigidBody(float mass);
};