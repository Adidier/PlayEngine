#include "Base/GameObject.h"
#include "Graphic/Model.h"
#include "Physics/RigidBody.h"

class Cylinder : public GameObject
{
private:
	RigidBody* rigidbody;
	Transform transform;
	Graphic::Model* model;
public:
	Cylinder();
	virtual ~Cylinder();
	void Draw() override;
	void Update(unsigned int delta) override;
	void OnTriggerEnter(void* ptr) override;
};