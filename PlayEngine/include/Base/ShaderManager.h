#pragma once
#include "../Export.h"
#include<map>
#include "../Graphic/Shader.h"
#include "../Graphic/Camera.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

class PLAYENGINE ShaderManager
{
public:
	void LoadShaders(const std::string& name);
	void LoadShaders(const std::string& name, const std::string& pathV, const std::string& pathF);
	static ShaderManager* getPtr();
	void initShader(Camera* camera);
	void draw();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	void Activate(const std::string& path);
	Shader* GetCurrentShader();

private:
	ShaderManager();
	std::map<std::string, Shader> shaderList;
	Shader* currentShader;
	static ShaderManager* ptr;
	Camera* camera;
	glm::mat4 projection;
	
	GLuint color1, color2;
	GLuint  uniformEyePosition = 0,
		uniformAmbientIntensity = 0, uniformAmbientColour = 0, uniformDirection = 0, uniformDiffuseIntensity = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0,
		myMaterialAmbient = 0, myLightAmbient = 0;


	DirectionalLight mainLight;
	PointLight pointLights[MAX_POINT_LIGHTS];
};

