#ifndef __OBJECT_H
#define __OBJECT_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


class Shader;
class Object {
public:
	virtual void draw()=0;//接口，每一个Object必须draw
};

//Canvas, background
class Canvas:Object{
private:
	float _red, _green, _blue, _alpha;
public:
	Canvas();
	Canvas(float red, float green, float blue, float alpha = 1.0f);
	Canvas(glm::vec3 bgColor, float alpha = 1.0f);
	Canvas(glm::vec4 bgColor);

	~Canvas();
	virtual void draw();
	void drawObj(Object* obj);
};
#endif