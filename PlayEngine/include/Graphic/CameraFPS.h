#pragma once
#include "../Export.h"
#include "Camera.h"
#include <map>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>

class PLAYENGINE CameraFps : public Camera
{
public:
	void keyControl(std::map<int, bool> keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);
};

