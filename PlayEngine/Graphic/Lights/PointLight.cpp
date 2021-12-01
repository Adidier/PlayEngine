#include "Graphic/Lights/PointLight.h"
#include "Base/ShaderManager.h"

PointLight::PointLight(int _index) : Light()
{
	index = _index;
	position = glm::vec3(0, 0, 0);
}

PointLight::PointLight(int _index, glm::vec3 _position, glm::vec3 _ambient,
	glm::vec3 _difuse, glm::vec3 _specular,
	float _constant, float _linear, float _exponent) : Light(_ambient, _difuse, _specular)
{
	index = _index;
	position = _position;
	constant = _constant;
	linear = _linear;
	exponent = _exponent;
}

void PointLight::UseLight()
{
	ShaderManager::getPtr()->Activate("phong-shader-lighting");
	auto currentShader = ShaderManager::getPtr()->GetCurrentShader();
	std::string light = "pointLights[" + std::to_string(index) + "]";
	currentShader->SetUniform(light+".base.ambientColor", ambientColor);
	currentShader->SetUniform(light + ".base.diffuseColor", diffuseColor);
	currentShader->SetUniform(light + ".base.specularColor", specularColor);

	currentShader->SetUniform(light + ".position", position);
	currentShader->SetUniform(light + ".constant", constant);
	currentShader->SetUniform(light + ".linear", linear);
	currentShader->SetUniform(light + ".exponent", exponent);
}

PointLight::~PointLight()
{

}