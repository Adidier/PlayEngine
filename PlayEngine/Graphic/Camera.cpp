#include "Graphic/Camera.h"
#include "Base/ResourceManager.h"
Camera::Camera() 
{
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	firstMove = true;
	nextPosition = position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	
	front = glm::vec3(0.0f, 0.0f, 1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	audioPlayer = (AudioPlayer*)ResourceManager::GetPtr()->GetElement("laser_shot");

	update();
}

void Camera::keyControl(std::map<int, bool> keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_J])
	{
		audioPlayer->PlaySoundEfect();
	}

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

glm::vec3 Camera::getCameraPosition()
{
	return nextPosition;
}

glm::vec3 Camera::getFront()
{
	return front;
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
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

glm::mat4 Camera::calculateViewMatrix()
{
	position = nextPosition;
	return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
	front.x = cos(glm::radians(-yaw));
	front.y = sin(glm::radians(-pitch));
	front.z = sin(glm::radians(-yaw));
	front = glm::normalize(front);
	
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{
}
	