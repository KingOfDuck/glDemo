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
	光照接口类，必须继承才可使用
 * 光照提供接口
 * Getters&Setters
 * 覆盖掉的属性:
 * _position(vec3), _direction(float->vec3)

 * @warning 必须继承以下接口
 * void paint()
 * void draw()
 * void step()
 * @examples
 * 对于不用绘图的光源：
	class TL: public Light{
	public:
		TL():Light(),Object(NULL){}
	}
 * 对于需要绘制的光源，见vertLight
*/ 
class Light: virtual public Object{
	friend class LightManager;
protected:
	glm::vec3 _position;//光位置
	glm::vec3 _direction;//方向，点光源无用
	glm::vec3 _ambient;//环境光颜色
	glm::vec3 _diffuse;//漫反射光颜色
	glm::vec3 _specular;//高光颜色（一般为全1）
	float _constant;//点光衰减常数项
	float _linear;//点光衰减一次项
	float _quadratic;//点光衰减二次项
	float _cutOff;//聚光内角
	float _outerCutOff;//聚光外角
	LightManager::type _type;//灯光类型
public:
	Light(Stage *s);

	inline bool isCameraSpot() { return _type == LightManager::type::cameraspot; }
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

	virtual void draw() = 0;
	virtual void step() = 0;
	virtual void paint() = 0;
	//setters 设置为protected,只允许LightManager访问
protected:
	//光源位置
	virtual void setPosition(float x, float y, float z);//virtual为了vertLight继承
	virtual void setPosition(const glm::vec3& pos);
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
	//光源位置
	void setPosition(float x, float y, float z);//virtual为了vertLight继承
	void setPosition(const glm::vec3& pos);
};
#endif