#include "GameObject.h"
#include "Player.h"
#include "Graphic/Model.h"
#include "Physics/RigidBody.h"
#include "ScriptEnemy.h"

class Sphere : public GameObject
{
private:
	RigidBody* rigidBody;
	Transform transform;
	Graphic::Model* model;
public:
	Sphere();
	void Draw() override;
	void Update(unsigned int delta) override;
};
