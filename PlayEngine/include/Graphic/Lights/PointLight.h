#pragma once
#include "../../Export.h"
#include "Light.h"

class PLAYENGINE PointLight : public Light
{
private:
	float constant = 1;
	float linear = 1;
	float exponent = 1;
	glm::vec3 position;
	int index;
public:
	PointLight(int index);
	PointLight(int index, glm::vec3 _position, glm::vec3 _ambient,
		glm::vec3 _difuse, glm::vec3 _specular, float _constant, float _linear, float _exponent);

	virtual void UseLight() override;
	~PointLight();
};
