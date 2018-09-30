/** @filename object.h
* @brief Base objects
* @update 2018/09/25 Move all base objects to object.h
*/
#ifndef __OBJECT_H
#define __OBJECT_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

#define OBJCET_NAME_MODEL			"model"				//ģ�;���
#define OBJECT_NAME_MATERIAL		"material"
#define OBJECT_ATTR_DIFFCOLOR		".diffuse_color"
#define OBJECT_ATTR_SPECCOLOR		".specular_color"	
#define OBJECT_ATTR_USETEXTURE		".useTexture"		//Use Texutre
#define OBJECT_ATTR_DIFFTEX			".diffuse"			//Deffuse Texture
#define OBJECT_ATTR_SPECTEX			".specular"			//Specular Texture
#define OBJECT_ATTR_SHININESS		".shininess"
#define OBJECT_ATTR_NUMDIFFTEX		".nDiffuse"
#define OBJECT_ATTR_NUMSPECTEX		".nSpecular"

class Shader;
class Texture;
class Stage;
class Material;
class Drawer;
/** @class Object
* @brief Base class for all objects. An object must be belonged to a stage.
*/
class Object {
	friend class Stage;
protected:
	Stage *_stage;//ÿһ��Object�����������stage�У���¼��Stage
public:
	Object(Stage *s) :_stage(s) { _stage = s; }
	virtual void step() = 0;
	virtual ~Object(){}
protected:
	virtual void draw() = 0;//�ӿڣ�ÿһ��Object����draw
private:
	Object();
};

//Canvas, background
class Canvas: public Object{
	friend class Stage;
private:
	float _red, _green, _blue, _alpha;
public:
	Canvas();
	Canvas(float red, float green, float blue, float alpha = 1.0f);
	Canvas(glm::vec3 bgColor, float alpha = 1.0f);
	Canvas(glm::vec4 bgColor);


	//Canvas������step
	inline void step() {};
protected:
	void draw();

	~Canvas();
};


/** @class Entity
* @brief Entity Object, ʵ�����壬�����������λ����Ϣ���ṩ��ά�任�ӿ�
* @inderface void step()
* @banned Entity()
*/
class Entity : virtual public Object {
protected:
	//Geometric
	glm::vec3 _position;//λ�ã���ʼ��ԭ��
	glm::vec3 _scale;//���ţ���ʼΪ1
	glm::vec3 _rotate;//���峯�򣬳�ʼΪ0
	glm::mat4 _model;//ģ����ͼ���󣬳�ʼ��Ϊ��λ����
	Drawer *_drawer;//��ͼģ�飬��ʵ�����
public:
	Entity(Stage* s);
	virtual ~Entity();

	virtual void paint() = 0;
	virtual void step() = 0;
	inline const glm::vec3& getPosition() { return _position; }
	inline const glm::mat4& getModelMatrix() { return _model; }

	//�ƶ�
	void move(float x, float y, float z);
	//�ƶ���
	void moveTo(float x, float y, float z);
	//ֻ������תz��
	void rotate(float zdegree);
	//ֻ������תz��
	void rotateTo(float zdegree);
	//������ת
	void rotate(float degree, const glm::vec3&axis);
	//����
	void scale(float x, float y, float z);
	//������
	void scaleTo(float x, float y, float z);

protected:
	//һ�㲻�ܼ̳С�ʵ��drawͨ��drawerʵ��
	virtual void draw();


private:
	Entity();
};



/** @class vertObejct(interface)
* @brief ���ɶ������壬�̳���Entity�����������ö����ʽ����ͼ����ʣ�����ӵ���Զ������ݵ�����
	���ɶ����������ɫ����Ҫ�������ã���ˣ�ͨ����˵�����ɶ��������paint�������£�
	1���Ƿ���Ҫ����Ĭ����ɫ��������ǣ������ֶ���д����/Ƭ����ɫ����ʹ��setShader()����
	2������д��paint()�����У�ͨ��_drawer->gl_getShader()�����ɫ��
	3��ʹ��shader->setParameter()��������������Ҫ���ݵ�uniform����
	4��ʹ��glDrawArray()/glDrawElement()���������ɶ�������
	ͨ����˵��shader��Ҫ���õĲ����У�
		�ƹ�setAmbient/Point/SpotLight()
		����material.diffuse/specular
		�ӵ�viewPos
		����viewDir
		��ͼ���� model/view/projection
	ͬʱ��ӵ����ͼ�����廹��Ҫ������ͼ
		texture[0]->use()
* @interface void step()
* @interface void draw()
*/
class vertObject : public Entity{
protected:
	float * _vertices;//��������
	unsigned int _nvert;//�������
	unsigned int * _indices;//��������
	unsigned int _nIndices;//��������
	std::vector<int> _format;//�������и�ʽ
	Material* _material;//���ʣ���ѡ�������޲��ʣ�
	std::vector<Texture*> _texture;//������ѡ
public:
	vertObject(Stage *s);
	virtual ~vertObject();

	virtual void step() = 0;
	virtual void paint() = 0;
protected:
	//���ö����ʽ
	//@oneLineFormat ÿһ�и�ʽ˵�������磺2 2 3��ʾһ����2+2+3=7������
	//	�ҷ�Ϊ2��2��3����
	void setupFormat();
	void setVerticesFormatf(int number, int* groups);
	//��������
	void setIndices(unsigned int* indices, unsigned int _nindices);
	//���ö���
	void setVertices(float*vertices, int nvert);
};
#endif