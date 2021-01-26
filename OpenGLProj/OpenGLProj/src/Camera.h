#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"

class Camera
{
private:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	float fov;
	float speed;

	float yaw;
	float pitch;
	float sensitivity;

	bool cameraEnable = true;
public:
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront);
	~Camera() {};

	void rotate(float yaw, float pitch);

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

};

