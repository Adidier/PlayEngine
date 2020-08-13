#include "Graphic/Camera.h"
namespace Graphics {
	Camera::Camera() {}

	Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
	{
		firstMove = true;
		nextPosition = position = startPosition;
		worldUp = startUp;
		yaw = startYaw;

		front = glm::vec3(0.0f, 0.0f, -1.0f);

		moveSpeed = startMoveSpeed;
		turnSpeed = startTurnSpeed;

		update();
	}

	void Camera::keyControl(std::map<int, bool> keys, GLfloat deltaTime)
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
	}

	glm::vec3 Camera::getCameraPosition()
	{
		return nextPosition;
	}


	glm::vec3 Camera::getCameraRotation()
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


		update();
	}

	glm::mat4 Camera::calculateViewMatrix()
	{
		position = nextPosition;
		return glm::lookAt(position, position + front, up);
	}

	void Camera::update()
	{
		front.x = cos(glm::radians(yaw));
		front.y = 0;//sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw));
		front = glm::normalize(front);

		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}


	Camera::~Camera()
	{
	}
}
	