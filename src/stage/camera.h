#ifndef __CAMERA_H
#define __CAMERA_H
#include <Windows.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

//camera class
/*
	Camera has two directions: pitch(y-offset) and yaw(z-offset)

*/
#define CAMERA_DEFAULTHEIGHT 0.0f

class Camera {
private:
	float _pitch;
	float _yaw;
	float _speed;//camera speed
	glm::vec3 _pos;//position
	glm::vec3 _front;//front vector
	glm::vec3 _up;//up vector
	glm::mat4 _view;//view matrix
public:
	Camera();
	//移动
	void move(float x, float y, float z);
	//移动至
	void moveTo(float x, float y, float z);
	//向前移动
	void moveFront(float val);
	//向左移动
	void moveLeft(float val);

	//旋转俯仰角
	void rotate(float pitch, float yaw);
	//旋转至俯仰角
	void rotateTo(float pitch, float yaw);

	void step();

	//设置速度
	inline void setSpeed(float s) { _speed = s; }
	inline const glm::vec3& getPosition() {
		return _pos;
	}
	inline const glm::vec3& getDirection() {
		return _front;
	}
	//获取视图矩阵
	inline const glm::mat4& getViewMatrix() {
		return _view;
	}
};
#endif