#ifndef __LIGHT_H
#define __LIGHT_H

#include "object.h"
#include "manager/LightManager.h"
#include <glm/vec3.hpp>
/* Light Class (interface)
 * Light is a drawble object, but you can decide to draw the light source object or not.
   If no vertices are given, the light source object won't be rendered, you cannot see where the light is.
   But the light will still act on objects.

 * 光照提供接口
 * Getters&Setters
 * 覆盖掉的属性:
 * _position(vec3), _direction(float->vec3)

 * @WARNING CANNOT be used directly, implement(PUBLIC) Light class and override the functions
 * @void draw()
 * @void step()
*/ 
class Light : protected drawObject{
	friend class LightManager;
protected:
	glm::vec3 _direction;//方向，点光源无用
	glm::vec3 _ambient;//环境光颜色
	glm::vec3 _diffuse;//漫反射光颜色
	glm::vec3 _specular;//高光颜色（一般为全1）
	float _constant;//点光衰减常数项
	float _linear;//点光衰减一次项
	float _quadratic;//点光衰减二次项
	float _cutOff;//聚光内角
	float _outerCutOff;//聚光外角
	LightManager::lighttype _type;//灯光类型
public:
	Light(float* vertices = NULL, int nvert = 0, Stage *s = NULL);

	inline bool isCameraSpot() { return _type == LightManager::lighttype::cameraspot; }
	//getters
	//光源位置
	inline const glm::vec3& getPosition() { return _position; }
	//光源方向
	inline const glm::vec3& getDirection() { return _direction; }
	//环境光颜色
	inline const glm::vec3& getAmbientColor() { return _ambient; }
	//漫反射光颜色
	inline const glm::vec3& getDiffuseColor() { return _diffuse; }
	//高光颜色
	inline const glm::vec3& getSpecularColor() { return _specular; }
	//衰减常量
	inline float getConstant() { return _constant; }
	//衰减一次项
	inline float getLinear() { return _linear; }
	//衰减二次项
	inline float getQuadratic() { return _quadratic; }
	//内角
	inline float getCutOff() { return _cutOff; }
	//外角
	inline float getOuterCutOff() { return _outerCutOff; }

	virtual void step() = 0;
	virtual void paint() = 0;
	//setters 设置为protected,只允许LightManager访问
protected:
	//光源位置
	void setPosition(float x, float y, float z);
	void setPosition(const glm::vec3& pos);
	//光源方向
	void setDirection(float x, float y, float z);
	void setDirection(const glm::vec3& pos);
	//环境光颜色
	void setAmbientColor(float red, float green, float blue);
	//漫反射光颜色
	void setDiffuseColor(float red, float green, float blue);
	//高光颜色
	void setSpecularColor(float red, float green, float blue);
	//衰减常量
	void setConstant(float val);
	//衰减一次项
	void setLinear(float val);
	//衰减二次项
	void setQuadratic(float val);
	//内角
	void setCutOff(float val);
	//外角
	void setOuterCutOff(float val);

	//点光源衰减等级
	void setPointLightLevel(float level);

	
private:
	Light();
};
#endif