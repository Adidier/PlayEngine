#include "Base/ShaderManager.h"
#include "Base/PEPlatform.h"
#include "Base/ResourceManager.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
ShaderManager* ShaderManager::ptr;

ShaderManager::ShaderManager() : currentShader(nullptr), camera(nullptr)
{
	LoadShaders("default");
}

void ShaderManager::LoadShaders(const std::string& name, const std::string& pathV, const std::string& pathF)
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(pathV.c_str(), pathF.c_str());
	shaderList[name] = (*shader1);
	Activate(name);
}


void ShaderManager::LoadShaders(const std::string& name)
{
	Shader* shader1 = new Shader();
	auto resourceManager = ResourceManager::GetPtr();
	std::string vertexShaderPath = resourceManager->GetPath(ResourceType::VertexShader, name );
	std::string fragmentShaderPath = resourceManager->GetPath(ResourceType::FragmentShader, name);
	shader1->CreateFromFiles(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
	shaderList[name] = (*shader1);
	Activate(name);
}

ShaderManager* ShaderManager::getPtr()
{
	if (ptr == nullptr)
	{
		ptr = new ShaderManager();
	}
	return ptr;
}

glm::mat4 ShaderManager::GetViewMatrix()
{
	if (camera != nullptr)
	{
		return camera->calculateViewMatrix();
	}
	return glm::mat4(1);
}

glm::mat4 ShaderManager::GetProjectionMatrix()
{
	return projection;
}

void ShaderManager::draw()
{
	if (currentShader != nullptr && camera != nullptr)
	{
		currentShader->UseShader();
		currentShader->SetUniform("projection", projection);
		currentShader->SetUniform("view", camera->calculateViewMatrix());

		mainLight = DirectionalLight(0.5f, 0.5f, 0.5f,
			1.0, 1.0f,
			0.0f, 0.0f, -1.0f);

		unsigned int pointLightCount = 0;
		pointLights[0] = PointLight(0.0f, 1.0f, 0.0f,
			0.7f, 1.2f,
			0.0f, 0.0f, 0.0f,
			1.0f, 0.2f, 0.1f);
		pointLightCount++;
		pointLights[1] = PointLight(1.0f, 1.0f, 1.0f,
			.7f, .7f,
			-1.0f, 0.0f, 0.0f,
			1.0f, 0.2f, 0.1f);
		pointLightCount++;

	//	currentShader->SetDirectionalLight(&mainLight);
	//	currentShader->SetPointLights(pointLights, pointLightCount);
	}
}
void ShaderManager::initShader(Camera* camera)
{
	if (currentShader != nullptr)
	{
		this->camera = camera;
		projection = glm::perspective(45.0f, (float)Platform::GetPtr()->GetWidth() / Platform::GetPtr()->GetHeight(), 0.1f, 1000.0f);//Adidier parametrizar el FOV
	}
}

void ShaderManager::Activate(const std::string& name)
{
	if (shaderList.find(name) != shaderList.end())
	{
		currentShader = &shaderList[name];
		
		//uniformAmbientColour = currentShader->GetAmbientColourLocation();
		//uniformAmbientIntensity = currentShader->GetAmbientIntensityLocation();
		//uniformDirection = currentShader->GetDirectionLocation();
		//uniformDiffuseIntensity = currentShader->GetDiffuseIntensityLocation();
	}
}

Shader* ShaderManager::GetCurrentShader()
{
	return currentShader;
}