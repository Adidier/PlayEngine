#pragma once
#include "../Export.h"
#include<map>
#include "../Graphic/Shader.h"
#include "../Graphic/Camera.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
namespace Base {
	const int MAX_POINT_LIGHTS = 3;
	class PLAYENGINE ShaderManager
	{
	public:
		void LoadShaders(const std::string& name, const std::string& pathV, const std::string& pathF);
		const char* vShaderDefault = "Assets/Shaders/Default/default.vert";
		const char* fShaderDefault = "Assets/Shaders/Default/default.frag";
		static ShaderManager* getPtr();
		void initShader(Graphics::Camera* camera);
		void draw();
		GLint GetSpecularIntensityLocation();
		GLint GetShininessLocation();
		GLint GetColor1();
		GLint GetColor2();
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		void Activate(const std::string& path);
		GLuint GetUniformId(const std::string& id);
		GLuint GetmainTex();
		GLuint GetrTex();
		GLuint GetgTex();
		GLuint GetbTex();
		GLuint GetblendTexture();
		GLuint GetNormalTexture();

	private:
		ShaderManager();
		std::map<std::string, Graphics::Shader> shaderList;
		Graphics::Shader* currentShader;
		static ShaderManager* ptr;
		Graphics::Camera* camera;
		glm::mat4 projection;

		GLuint color1, color2;
		GLuint  uniformEyePosition = 0,
			uniformAmbientIntensity = 0, uniformAmbientColour = 0, uniformDirection = 0, uniformDiffuseIntensity = 0,
			uniformSpecularIntensity = 0, uniformShininess = 0,
			myMaterialAmbient = 0, myLightAmbient = 0;


		Graphics::Lights::DirectionalLight mainLight;
		Graphics::Lights::PointLight pointLights[MAX_POINT_LIGHTS];

		GLuint mainTex;
		GLuint rTex;
		GLuint gTex;
		GLuint bTex;
		GLuint blendTexture;
		GLuint normalTexture;

	};
}

