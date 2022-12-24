#include "Graphic/CameraFPS.h"
#include "Base/ResourceManager.h"

void CameraFps::keyControl(std::map<int, bool> keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		nextPosition += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		nextPosition -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		nextPosition -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		nextPosition += right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		nextPosition += right * velocity;
	}
}

void CameraFps::mouseControl(GLfloat xChange, GLfloat yChange)
{
	if (firstMove) {
		prevXPos = xChange;
		prevYPos = yChange;
		firstMove = false;
	}

	float xoffset = xChange - prevXPos;
	float yoffset = yChange - prevYPos;

	prevXPos = xChange;
	prevYPos = yChange;

	xoffset *= turnSpeed;
	yoffset *= turnSpeed;

	yaw += xoffset;
	pitch += yoffset;
	update();
}	