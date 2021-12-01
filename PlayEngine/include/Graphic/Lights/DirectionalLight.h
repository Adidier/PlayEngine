#pragma once
#include "../../Export.h"
#include "Light.h"


class PLAYENGINE DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 difuse, glm::vec3 specular, float intensity);
	virtual void UseLight() override;
	~DirectionalLight();
private:
	glm::vec3 direction;
	float intensity;
};

