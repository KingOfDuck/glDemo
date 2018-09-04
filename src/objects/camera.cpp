#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
	_pos = glm::vec3(0.0f, 0.0f, CAMERA_DEFAULTHEIGHT);//默认高度
	_up = glm::vec3(0.0f, 1.0f, 0.0f);//y轴正方向
	_front = glm::vec3(0.0f, 0.0f, -1.0f);//目标位置与camera的距离
	_pitch = 0.0f;
	_yaw = 0.0f;
}
void Camera::step() {
	_view = glm::lookAt(_pos, _pos + _front, _up);
}