#ifndef __OBJECT_H
#define __OBJECT_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>


class Shader;
class Texture;
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
};

//Object with a shader
class drawObject : public Object {
protected:
	unsigned int _vbo;//顶点缓冲对象
	unsigned int _vao;//顶点数组对象
	unsigned int _ebo;//数组索引，可选
	glm::vec3 _position;//位置
	glm::vec3 _model;//模型视图矩阵
	Shader* _shader;//着色器，必须
	std::vector<Texture*> _texture;//纹理，可选
public:
	virtual void draw() = 0;
};
#endif