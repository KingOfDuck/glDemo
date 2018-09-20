#ifndef __OBJECT_H
#define __OBJECT_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

class Shader;
class Texture;
class Stage;
class Material;
class Object {
protected:
	Stage *_stage;//每一个Object都必须包含于stage中，记录其Stage
public:
	Object(Stage *s) :_stage(s) { _stage = s; }
	virtual void step() = 0;
	virtual void draw() = 0;//接口，每一个Object必须draw
private:
	Object();
};

//Canvas, background
class Canvas: public Object{
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
* Object with a shader and material
* @interface void draw()
* @inderface void step()
* @banned drawObject()
*/
class drawObject : public Object {
protected:
	//Data
	unsigned int _vbo;//顶点缓冲对象
	unsigned int _vao;//顶点数组对象
	unsigned int _ebo;//数组索引，可选
	float * _vertices;//顶点数据
	int _nvert;//顶点个数
	std::vector<int> _format;//顶点排列格式

	//Geometric
	glm::vec3 _position;//位置，初始在原点
	glm::vec3 _scale;//缩放，初始为1
	glm::vec3 _rotate;//物体朝向，初始为0
	glm::mat4 _model;//模型视图矩阵，初始化为单位矩阵

	//Properties
	Shader* _shader;//着色器，必须
	Material* _material;//材质，可选（光照无材质）
	std::vector<Texture*> _texture;//纹理，可选
	
public:
	drawObject(float*vertices, int nvert, Stage* s);
	~drawObject();

	void draw();
	virtual void step() = 0;
	virtual void paint() = 0;

	inline unsigned int getVBO() { return _vbo; }
	inline unsigned int getVAO() { return _vao; }
	inline const glm::vec3& getPosition() { return _position; }

	//移动
	void move(float x, float y, float z);
	//移动至
	void moveTo(float x, float y, float z);
	//只允许旋转z轴
	void rotate(float zdegree);
	//只允许旋转z轴
	void rotateTo(float zdegree);
	//开放旋转
	void rotate(float degree, const glm::vec3&axis);
	//缩放
	void scale(float x, float y, float z);
	//缩放至
	void scaleTo(float x, float y, float z);
	//配置shader
	void setShader(Shader* s) { _shader = s; }

protected:
	//设置顶点格式
	//@oneLineFormat 每一行格式说明，例如：2 2 3表示一行有2+2+3=7个数据
	//	且分为2，2，3三组
	void setVerticesFormatf(std::vector<int> oneLineFormat);
	void setVerticesFormatf(int number, int* groups);

	//设置索引格式
	void setIndicesFormat();

private:
	drawObject();
};
#endif