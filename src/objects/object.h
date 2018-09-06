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
	Stage *_stage;//ÿһ��Object�����������stage�У���¼��Stage
public:
	Object(Stage *s) :_stage(s){}
	virtual void step() = 0;
	virtual void draw() = 0;//�ӿڣ�ÿһ��Object����draw
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

	//Canvas������step
	inline void step() {};

	~Canvas();
};

//Object with a shader
class drawObject : public Object {
protected:
	unsigned int _vbo;//���㻺�����
	unsigned int _vao;//�����������
	unsigned int _ebo;//������������ѡ
	glm::vec3 _position;//λ��
	float _direction;//����
	glm::mat4 _model;//ģ����ͼ����
	Shader* _shader;//��ɫ��������
	std::vector<Texture*> _texture;//������ѡ
public:
	virtual void draw() = 0;
	virtual void step() = 0;
	drawObject(Stage* s);
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
private:
	drawObject();
};
#endif