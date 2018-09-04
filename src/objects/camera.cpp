#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
	_pos = glm::vec3(0.0f, 0.0f, CAMERA_DEFAULTHEIGHT);//Ĭ�ϸ߶�
	_up = glm::vec3(0.0f, 1.0f, 0.0f);//y��������
	_front = glm::vec3(0.0f, 0.0f, -1.0f);//Ŀ��λ����camera�ľ���
	_pitch = 0.0f;
	_yaw = 0.0f;
}
void Camera::step() {
	_view = glm::lookAt(_pos, _pos + _front, _up);
}