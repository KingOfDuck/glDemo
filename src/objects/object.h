#ifndef __OBJECT_H
#define __OBJECT_H
#endif
#include <gl/GL.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


class Shader;
class Object {
public:
	virtual void draw()=0;//�ӿڣ�ÿһ��Object����draw
};

//Canvas, draw items on it!
class Canvas:Object{
private:
	GLfloat _red, _green, _blue, _alpha;
public:
	Canvas();
	Canvas(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 1.0f);
	Canvas(glm::vec3 bgColor, GLfloat alpha = 1.0f);
	Canvas(glm::vec4 bgColor);

	~Canvas();
	virtual void draw();
};