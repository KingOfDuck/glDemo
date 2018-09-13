#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera():_speed(1.0f),_pitch(0.0f),_yaw(0.0f){
	_pos = glm::vec3(0.0f, 0.0f, CAMERA_DEFAULTHEIGHT);//默认高度
	_up = glm::vec3(0.0f, 1.0f, 0.0f);//y轴正方向
	_front = glm::vec3(1.0f, 0.0f, 0.0f);//目标位置与camera的距离
	_pitch = 0.0f;
	_yaw = 0.0f;
}
void Camera::step() {
	_view = glm::lookAt(_pos, _pos + _front, _up);
}

void Camera::move(float x, float y, float z) {
	_pos.x += x;
	_pos.y += y;
	_pos.z += z;
}

void Camera::moveTo(float x, float y, float z) {
	_pos.x = x;
	_pos.y = y;
	_pos.z = z;
}

void Camera::moveFront(float val) {
	_pos += (_speed * val) * _front;
}

void Camera::moveLeft(float val) {
	_pos += glm::normalize(-glm::cross(_front, _up)) * (_speed * val);
}

void Camera::rotate(float pitch, float yaw) {
	_pitch += pitch;
	_yaw += yaw;

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	_front = glm::normalize(front);
}

void Camera::rotateTo(float pitch, float yaw) {
	_pitch = pitch;
	_yaw = yaw;

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	glm::vec3 front(1.0f);
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	_front = glm::normalize(front);

}