#ifndef __OBJECT_H
#define __OBJECT_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>


class Shader;
class Texture;
class Object {
public:
	virtual void draw()=0;//�ӿڣ�ÿһ��Object����draw
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
	unsigned int _vbo;//���㻺�����
	unsigned int _vao;//�����������
	unsigned int _ebo;//������������ѡ
	glm::vec3 _position;//λ��
	glm::vec3 _model;//ģ����ͼ����
	Shader* _shader;//��ɫ��������
	std::vector<Texture*> _texture;//������ѡ
public:
	virtual void draw() = 0;
};
#endif