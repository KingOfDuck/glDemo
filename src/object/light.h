#ifndef __LIGHT_H
#define __LIGHT_H

#include "object.h"
#include "manager/LightManager.h"
#include <glm/vec3.hpp>
#define LIGHT_ATTR_MATERIAL			".material"
#define LIGHT_ATTR_POSITION			".position"
#define LIGHT_ATTR_DIRECTION		".direction"
#define LIGHT_ATTR_AMBIENT			".ambient"
#define LIGHT_ATTR_DIFFUSE			".diffuse"
#define LIGHT_ATTR_SPECULAR			".specular"
#define LIGHT_ATTR_ISCAMERASPOT		".cameraSpot"
#define LIGHT_ATTR_CONSTANT			".constant"
#define LIGHT_ATTR_LINEAR			".linear"
#define LIGHT_ATTR_QUADRATIC		".quadratic"
#define LIGHT_ATTR_CUTOFF			".cutOff"
#define LIGHT_ATTR_OUTERCUTOFF		".outerCutOff"
#define LIGHT_BOOL_HASDIRLIGHT		"hasdirlight"
#define LIGHT_NUMBER_POINTLIGHT		"npointlight"
#define LIGHT_NUMBER_SPOTLIGHT		"nspotlight"
#define LIGHT_NAME_DIRLIGHT			"dirLight"
#define LIGHT_NAME_POINTLIGHT		"pointLights"
#define LIGHT_NAME_SPOTLIGHT		"spotLights"

/**@class Light(interface)
 * @brief light
	���սӿ��࣬����̳вſ�ʹ��
 * �����ṩ�ӿ�
 * Getters&Setters
 * ���ǵ�������:
 * _position(vec3), _direction(float->vec3)

 * @warning ����̳����½ӿ�
 * void paint()
 * void draw()
 * void step()
 * @examples
 * ���ڲ��û�ͼ�Ĺ�Դ��
	class TL: public Light{
	public:
		TL():Light(),Object(NULL){}
	}
 * ������Ҫ���ƵĹ�Դ����vertLight
*/ 
class Light: virtual public Object{
	friend class LightManager;
protected:
	glm::vec3 _position;//��λ��
	glm::vec3 _direction;//���򣬵��Դ����
	glm::vec3 _ambient;//��������ɫ
	glm::vec3 _diffuse;//���������ɫ
	glm::vec3 _specular;//�߹���ɫ��һ��Ϊȫ1��
	float _constant;//���˥��������
	float _linear;//���˥��һ����
	float _quadratic;//���˥��������
	float _cutOff;//�۹��ڽ�
	float _outerCutOff;//�۹����
	LightManager::type _type;//�ƹ�����
public:
	Light(Stage *s);

	inline bool isCameraSpot() { return _type == LightManager::type::cameraspot; }
	//getters
	//��Դλ��
	inline const glm::vec3& getPosition() { return _position; }
	//��Դ����
	inline const glm::vec3& getDirection() { return _direction; }
	//��������ɫ
	inline const glm::vec3& getAmbientColor() { return _ambient; }
	//���������ɫ
	inline const glm::vec3& getDiffuseColor() { return _diffuse; }
	//�߹���ɫ
	inline const glm::vec3& getSpecularColor() { return _specular; }
	//˥������
	inline float getConstant() { return _constant; }
	//˥��һ����
	inline float getLinear() { return _linear; }
	//˥��������
	inline float getQuadratic() { return _quadratic; }
	//�ڽ�
	inline float getCutOff() { return _cutOff; }
	//���
	inline float getOuterCutOff() { return _outerCutOff; }

	virtual void draw() = 0;
	virtual void step() = 0;
	virtual void paint() = 0;
	//setters ����Ϊprotected,ֻ����LightManager����
protected:
	//��Դλ��
	virtual void setPosition(float x, float y, float z);//virtualΪ��vertLight�̳�
	virtual void setPosition(const glm::vec3& pos);
	//��Դ����
	void setDirection(float x, float y, float z);
	void setDirection(const glm::vec3& pos);
	//��������ɫ
	void setAmbientColor(float red, float green, float blue);
	//���������ɫ
	void setDiffuseColor(float red, float green, float blue);
	//�߹���ɫ
	void setSpecularColor(float red, float green, float blue);
	//˥������
	void setConstant(float val);
	//˥��һ����
	void setLinear(float val);
	//˥��������
	void setQuadratic(float val);
	//�ڽ�
	void setCutOff(float val);
	//���
	void setOuterCutOff(float val);

	//���Դ˥���ȼ�
	void setPointLightLevel(float level);

	
private:
	Light();
};

/** @class vertLight
* @brief Drawble light, with custom vertices
* @overwrite arribute: _position
*  VertLight is a drawble object, but you can decide to draw the light source object or not.
   If no vertices are given, the light source object won't be rendered, you cannot see where the light is.
   But the light will still act on objects.
*/
class vertLight :public Light, public vertObject{
public:
	vertLight(Stage *s, float* vertices = NULL, int nvert = 0);

	void draw();
	virtual void step() = 0;
	virtual void paint() = 0;
protected:
	//��Դλ��
	void setPosition(float x, float y, float z);//virtualΪ��vertLight�̳�
	void setPosition(const glm::vec3& pos);
};
#endif