#include "Graphic/Lights/DirectionalLight.h"
#include "Base/ShaderManager.h"

DirectionalLight::DirectionalLight() : Light()
{
	intensity = 1.0;
	direction = glm::vec3(0,0,0);
}

DirectionalLight::DirectionalLight(glm::vec3 _direction, glm::vec3 _ambient,
	glm::vec3 _difuse, glm::vec3 _specular , float _intensity) : Light(_ambient, _difuse, _specular)
{
	direction = _direction;
	intensity = _intensity;
}

void DirectionalLight::UseLight()
{
	ShaderManager::getPtr()->Activate("phong-shader-lighting");
	auto currentShader = ShaderManager::getPtr()->GetCurrentShader();
	
	currentShader->SetUniform("directionalLight.base.ambientColor", glm::vec3(0.8, 0.8, 0.8));
	currentShader->SetUniform("directionalLight.base.diffuseColor", glm::vec3(1, 0.94, 0.0));
	currentShader->SetUniform("directionalLight.base.specularColor", glm::vec3(1, 1, 1));

	currentShader->SetUniform("directionalLight.direction", glm::vec3(0, 0, 0));
	currentShader->SetUniform("directionalLight.intensity", 40.01f);

}




DirectionalLight::~DirectionalLight()
{
}
