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
	//�ƶ�
	void move(float x, float y, float z);
	//�ƶ���
	void moveTo(float x, float y, float z);
	//��ǰ�ƶ�
	void moveFront(float val);
	//�����ƶ�
	void moveLeft(float val);

	//��ת������
	void rotate(float pitch, float yaw);
	//��ת��������
	void rotateTo(float pitch, float yaw);

	void step();

	//�����ٶ�
	inline void setSpeed(float s) { _speed = s; }
	inline const glm::vec3& getPosition() {
		return _pos;
	}
	inline const glm::vec3& getDirection() {
		return _front;
	}
	//��ȡ��ͼ����
	inline const glm::mat4& getViewMatrix() {
		return _view;
	}
};
#endif