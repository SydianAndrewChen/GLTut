#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"

const glm::vec3 xAxis(1.0f, 0.0f, 0.0f);
const glm::vec3 yAxis(0.0f, 1.0f, 0.0f);
const glm::vec3 zAxis(0.0f, 0.0f, 1.0f);

class Camera
{
private:

	float fov;
	float speed;

	float sensitivity;

	void updateCameraVectors()
	{
		// calculate the new Front vector
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		right = glm::normalize(glm::cross(front, yAxis));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		up = glm::normalize(glm::cross(right, front));
	}
public:
	bool cameraEnable = true;
	float yaw;
	float pitch;
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront);
	Camera(glm::vec3 cameraPos, float yaw, float pitch);
	~Camera() {};

	void rotate(float xoffset, float yoffset);

	void moveForward()
	{
		pos += speed * front;
	}
	void moveBack()
	{
		pos -= speed * front;
	}
	void moveLeft()
	{
		pos -= speed * right;
	}
	void moveRight()
	{
		pos += speed * right;
	}

	void zoom(float offset);
	float getFov() const { return fov; }

	void clearPos();

	glm::mat4 getLookAt() const { return glm::lookAt(pos, pos + front, up); }

	void setEnable(bool enable) { cameraEnable = enable; }

	float getSpeed() const { return speed; };

	void setSpeed(float val) { speed = val; }

	void setSensitivity(float val) { sensitivity = val; }

	glm::vec3 getPos() const{ return pos; }

};

