#ifndef __OBJECT_H
#define __OBJECT_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vector>


class Shader;
class Texture;
class Stage;
class Object {
protected:
	Stage *_stage;//每一个Object都必须包含于stage中，记录其Stage
public:
	Object(Stage *s) :_stage(s){}
	virtual void step() = 0;
	virtual void draw() = 0;//接口，每一个Object必须draw
	inline void setStage(Stage* s) {
		_stage = s;
	}
private:
	Object();
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

	void draw();

	//Canvas不存在step
	inline void step() {};

	~Canvas();
};

/*
* Object with a shader
* @interface void draw()
* @inderface void step()
* @banned drawObject()
*/
class drawObject : public Object {
protected:
	unsigned int _vbo;//顶点缓冲对象
	unsigned int _vao;//顶点数组对象
	unsigned int _ebo;//数组索引，可选
	float * _vertices;//顶点数据
	int _nvert;//顶点个数
	glm::vec3 _position;//位置，初始在原点
	float _direction;//方向，初始为0
	glm::mat4 _model;//模型视图矩阵，初始化为单位矩阵
	Shader* _shader;//着色器，必须
	std::vector<Texture*> _texture;//纹理，可选
public:
	drawObject(Stage* s);

	virtual void draw() = 0;
	virtual void step() = 0;
	
	inline unsigned int getVBO() { return _vbo; }
	inline unsigned int getVAO() { return _vao; }
	inline const glm::vec3& getPosition() { return _position; }

	void setTrans(const char* parameterName);
	//移动
	void move(float x, float y, float z);
	//移动至
	void moveTo(float x, float y, float z);
	//只允许旋转z轴
	void rotate(float zdegree);
	//只允许旋转z轴
	void rotateTo(float zdegree);
	//缩放
	void scale(float x, float y, float z);
	//缩放至
	void scaleTo(float x, float y, float z);
	//配置shader
	void setShader(Shader* s) { _shader = s; }
private:
	drawObject();
};
#endif