#ifndef __LIGHT_H
#define __LIGHT_H

#include "object.h"
#include "manager/LightManager.h"
#include <glm/vec3.hpp>
/* Light Class (interface)
 * Light is a drawble object, but you can decide to draw the light source object or not.
   If no vertices are given, the light source object won't be rendered, you cannot see where the light is.
   But the light will still act on objects.

 * �����ṩ�ӿ�
 * Getters&Setters
 * ���ǵ�������:
 * _position(vec3), _direction(float->vec3)

 * @WARNING CANNOT be used directly, implement(PUBLIC) Light class and override the functions
 * @void draw()
 * @void step()
*/ 
class Light : protected drawObject{
	friend class LightManager;
protected:
	glm::vec3 _direction;//���򣬵��Դ����
	glm::vec3 _ambient;//��������ɫ
	glm::vec3 _diffuse;//���������ɫ
	glm::vec3 _specular;//�߹���ɫ��һ��Ϊȫ1��
	float _constant;//���˥��������
	float _linear;//���˥��һ����
	float _quadratic;//���˥��������
	float _cutOff;//�۹��ڽ�
	float _outerCutOff;//�۹����
	LightManager::lighttype _type;//�ƹ�����
public:
	Light(float* vertices = NULL, int nvert = 0, Stage *s = NULL);

	inline bool isCameraSpot() { return _type == LightManager::lighttype::cameraspot; }
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

	virtual void step() = 0;
	virtual void paint() = 0;
	//setters ����Ϊprotected,ֻ����LightManager����
protected:
	//��Դλ��
	void setPosition(float x, float y, float z);
	void setPosition(const glm::vec3& pos);
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
#endif