#ifndef __CAMERA_H
#define __CAMERA_H
#include <Windows.h>
#include <gl/GLU.h>
#include <glm/vec3.hpp>

//camera class
/*
	Camera has two directions: pitch(y-offset) and yaw(z-offset)

*/
class Camera {
private:
	GLfloat _pitch;
	GLfloat _yaw;
	glm::vec3 _pos;//position
	glm::vec3 _front;//front vector
	glm::vec3 _up;//up vector
public:

};
#endif