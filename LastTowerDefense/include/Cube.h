#include "GameObject.h"
#include "Player.h"
#include "Graphic/Model.h"
#include "Physics/RigidBody.h"
#include "ScriptEnemy.h"

class Cube : public GameObject
{
private:
	RigidBody* rigidBody;
	Transform transform;
	Graphic::Model* model;
public:
	Cube();
	void Draw() override;
	void Update(unsigned int delta) override;
};
