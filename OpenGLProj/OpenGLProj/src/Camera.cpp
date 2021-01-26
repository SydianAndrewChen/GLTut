#include "Camera.h"

Camera::Camera(glm::vec3 __cPos, glm::vec3 __cFront):pos (__cPos), front (glm::normalize(__cFront)), 
	fov(30.0f), speed(2.5f), sensitivity(0.05f), yaw(0.0f), pitch(0.0f)
{

	ASSERT(glm::cross(__cFront, glm::vec3(0.0f, 0.0f, 1.0f)) != glm::vec3(0.0f, 0.0f, 0.0f));
	right = glm::cross(front, glm::vec3(0.0f, 0.0f, 1.0f));
	up = glm::cross(right, front);
}

void Camera::rotate(float xoffset, float yoffset)
{
	if (cameraEnable) {
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f) pitch = 89.0f;
		else if (pitch < -89.0f) pitch = -89.0f;

		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	}
}

void Camera::zoom(float offset)
{
	if (fov >= 1.0f && fov <= 45.0f)
	{
		fov -= offset;
	}
	if (fov <= 1.0f)
	{
		fov = 1.0f;
	}
	if (fov >= 45.0f)
	{
		fov = 45.0f;
	}
}
