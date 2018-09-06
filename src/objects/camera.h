#ifndef __CAMERA_H
#define __CAMERA_H
#include <Windows.h>
#include <gl/GLU.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

//camera class
/*
	Camera has two directions: pitch(y-offset) and yaw(z-offset)

*/
#define CAMERA_DEFAULTHEIGHT 3.0f

class Camera {
private:
	GLfloat _pitch;
	GLfloat _yaw;
	glm::vec3 _pos;//position
	glm::vec3 _front;//front vector
	glm::vec3 _up;//up vector
	glm::mat4 _view;//view matrix
public:
	Camera();
	//�ƶ�
	void move(float x, float y, float z);
	//�ƶ���
	void moveTo(float x, float y, float z);
	//��ת������
	void rotate(float pitch, float yaw);
	//��ת��������
	void rotateTo(float pitch, float yaw);

	void step();
	inline glm::mat4& getViewMatrix() {
		return _view;
	}
};
#endif