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
	static ShaderManager* GetPtr();
	void InitShader(Camera* camera);
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
};

