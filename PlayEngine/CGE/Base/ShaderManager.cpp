#include "Base/ShaderManager.h"
#include "Base/PEPlatform.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
namespace Base {
	ShaderManager* ShaderManager::ptr;

	ShaderManager::ShaderManager() : currentShader(nullptr)
	{
		LoadShaders("default", vShaderDefault, fShaderDefault);
	}

	void ShaderManager::LoadShaders(const std::string& name, const std::string& pathV, const std::string& pathF)
	{
		Graphics::Shader* shader1 = new Graphics::Shader();
		shader1->CreateFromFiles(pathV.c_str(), pathF.c_str());
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



	GLint ShaderManager::GetColor1()
	{
		return color1;
	}

	GLint ShaderManager::GetColor2()
	{
		return color2;
	}
	GLint ShaderManager::GetSpecularIntensityLocation()
	{
		return uniformSpecularIntensity;
	}
	glm::mat4 ShaderManager::GetViewMatrix()
	{
		return camera->calculateViewMatrix();
	}

	glm::mat4 ShaderManager::GetProjectionMatrix()
	{
		return projection;
	}

	GLuint ShaderManager::GetmainTex()
	{
		return mainTex;
	}
	GLuint ShaderManager::GetrTex()
	{
		return rTex;
	}
	GLuint ShaderManager::GetgTex()
	{
		return gTex;
	}
	GLuint ShaderManager::GetbTex()
	{
		return bTex;
	}
	GLuint ShaderManager::GetblendTexture()
	{
		return blendTexture;
	}

	GLuint ShaderManager::GetNormalTexture()
	{
		return normalTexture;
	}



	GLint ShaderManager::GetShininessLocation()
	{
		return uniformShininess;
	}
	void ShaderManager::draw()
	{
		if (currentShader != nullptr)
		{
			currentShader->UseShader();
			glUniformMatrix4fv(currentShader->GetUniformId("projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(currentShader->GetUniformId("view"), 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));

			mainLight = Graphics::Lights::DirectionalLight(0.5f, 0.5f, 0.5f,
				1.0, 1.0f,
				0.0f, 0.0f, -1.0f);

			unsigned int pointLightCount = 0;
			pointLights[0] = Graphics::Lights::PointLight(0.0f, 1.0f, 0.0f,
				0.7f, 1.2f,
				0.0f, 0.0f, 0.0f,
				1.0f, 0.2f, 0.1f);
			pointLightCount++;
			pointLights[1] = Graphics::Lights::PointLight(1.0f, 1.0f, 1.0f,
				.7f, .7f,
				-1.0f, 0.0f, 0.0f,
				1.0f, 0.2f, 0.1f);
			pointLightCount++;

			currentShader->SetDirectionalLight(&mainLight);
			currentShader->SetPointLights(pointLights, pointLightCount);
		}
	}
	void ShaderManager::initShader(Graphics::Camera* camera)
	{
		if (currentShader != nullptr)
		{
			this->camera = camera;
			projection = glm::perspective(45.0f, (float)PEPlatform::GetPtr()->GetWidth() / PEPlatform::GetPtr()->GetHeight(), 0.1f, 1000.0f);


		}

	}

	GLuint ShaderManager::GetUniformId(const std::string& id)
	{
		return currentShader->GetUniformId(id);
	}

	void ShaderManager::Activate(const std::string& name)
	{
		if (shaderList.find(name) != shaderList.end())
		{
			currentShader = &shaderList[name];
			color1 = currentShader->GetUniformId("color1");
			color2 = currentShader->GetUniformId("color2");

			mainTex = currentShader->GetUniformId("mainTex");
			rTex = currentShader->GetUniformId("rTex");
			gTex = currentShader->GetUniformId("gTex");
			bTex = currentShader->GetUniformId("bTex");
			blendTexture = currentShader->GetUniformId("blendTex");
			normalTexture = currentShader->GetUniformId("normalMap");

			uniformAmbientColour = currentShader->GetAmbientColourLocation();
			uniformAmbientIntensity = currentShader->GetAmbientIntensityLocation();
			uniformDirection = currentShader->GetDirectionLocation();
			uniformDiffuseIntensity = currentShader->GetDiffuseIntensityLocation();
			uniformSpecularIntensity = currentShader->GetUniformId("material.specularIntensity");
			uniformShininess = currentShader->GetUniformId("material.shininess");
		}
	}
}
