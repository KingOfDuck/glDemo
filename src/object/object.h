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
	Stage *_stage;//ÿһ��Object�����������stage�У���¼��Stage
public:
	Object(Stage *s) :_stage(s) { _stage = s; }
	virtual void step() = 0;
	virtual void draw() = 0;//�ӿڣ�ÿһ��Object����draw
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

	//Canvas������step
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
	unsigned int _vbo;//���㻺�����
	unsigned int _vao;//�����������
	unsigned int _ebo;//������������ѡ
	float * _vertices;//��������
	int _nvert;//�������

	//Geometric
	glm::vec3 _position;//λ�ã���ʼ��ԭ��
	float _direction;//���򣬳�ʼΪ0
	glm::mat4 _model;//ģ����ͼ���󣬳�ʼ��Ϊ��λ����

	//Properties
	Material* _material;//���ʣ���ѡ�������޲��ʣ�
	Shader* _shader;//��ɫ��������
	std::vector<Texture*> _texture;//������ѡ
	
public:
	drawObject(Stage* s);
	~drawObject();

	virtual void draw() = 0;
	virtual void step() = 0;
	
	inline unsigned int getVBO() { return _vbo; }
	inline unsigned int getVAO() { return _vao; }
	inline const glm::vec3& getPosition() { return _position; }

	//Unused
	void setTrans(const char* parameterName);
	//�ƶ�
	void move(float x, float y, float z);
	//�ƶ���
	void moveTo(float x, float y, float z);
	//ֻ������תz��
	void rotate(float zdegree);
	//ֻ������תz��
	void rotateTo(float zdegree);
	//����
	void scale(float x, float y, float z);
	//������
	void scaleTo(float x, float y, float z);
	//����shader
	void setShader(Shader* s) { _shader = s; }
private:
	drawObject();
};
#endif