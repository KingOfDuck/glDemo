#ifndef __LIGHTMANAGER_H
#define __LIGHTMANAGER_H

#include <vector>
#include <map>
#include <glm/vec3.hpp>
#define LIGHTM_MAXPOINTLIGHT 16
#define LIGHTM_MAXSPOTLIGHT 16
#define LIGHTM_NODIRLIGHT -1

class Light;
 /*
 * 光照管理器
 * 提供接口：
	添加光照
	修改光照
	删除光照
	设定光照类型（环境光，聚光，点光，不使用）
	获取光照信息（环境光，聚光，点光）
 * 环境光数量必须小于1
 * 聚光数量每个镜头使用一个（耦合？）
 * 点光拥有最大数量（MAXPOINTLIGHT）
 */
class LightManager {
public:
	enum lighttype {
		unset,
		deleted,
		dir,//环境光
		point,//点光源
		spot,//聚光
		cameraspot,//第一人称聚光
	};
private:
	std::map<std::string, int> _lightmap;//map用来查找Light索引
	std::vector<Light*> _lights;//_lights存放实际灯光成员
	int _ambientlight;//环境光索引
	int _nspotlight;//聚光源数量
	int _npointlight;//点光源数量

public:
	LightManager();

	inline const Light* getLight(int index) { 
		if(index >=0 && index < _lights.size())
			return _lights[index]; 
		return NULL;
	}
	//添加灯光
	void addLight(Light* light, const char* name = NULL);
	void addLight(Light* light, const std::string& name = std::string());

	//ID删除灯光
	void deleteLight(int index);
	//地址删除灯光
	void deleteLight(Light* light);
	//按名称删除灯光
	void deleteLight(const char* lightname);
	//按名称删除灯光
	void deleteLight(const std::string& lightname);

	//Id设置灯光类型
	void setLightType(int index, lighttype type);
	//地址设置灯光类型
	void setLightType(Light* light, lighttype type);
	//按名称设置灯光类型
	void setLightType(const char* lightname, lighttype type);
	//按名称设置灯光类型
	void setLightType(const std::string& lightname, lighttype type);

	//修改光照信息
	//修改环境光颜色
	void setAmbientColor(int index, const glm::vec3& color);
	void setAmbientColor(int index, float red, float green, float blue);
	void setAmbientColor(Light* light, const glm::vec3& color);
	void setAmbientColor(Light* light, float red, float green, float blue);
	void setAmbientColor(const char* lightname, const glm::vec3& color);
	void setAmbientColor(const char* lightname, float red, float green, float blue);
	void setAmbientColor(const std::string& lightname, const glm::vec3& color);
	void setAmbientColor(const std::string& lightname, float red, float green, float blue);
	//修改漫反射光颜色
	void setDiffuseColor(int index, const glm::vec3& color);
	void setDiffuseColor(int index, float red, float green, float blue);
	void setDiffuseColor(Light* light, const glm::vec3& color);
	void setDiffuseColor(Light* light, float red, float green, float blue);
	void setDiffuseColor(const char* lightname, const glm::vec3& color);
	void setDiffuseColor(const char* lightname, float red, float green, float blue);
	void setDiffuseColor(const std::string& lightname, const glm::vec3& color);
	void setDiffuseColor(const std::string& lightname, float red, float green, float blue);
	//修改高光颜色
	void setSpecularColor(int index, const glm::vec3& color);
	void setSpecularColor(int index, float red, float green, float blue);
	void setSpecularColor(Light* light, const glm::vec3& color);
	void setSpecularColor(Light* light, float red, float green, float blue);
	void setSpecularColor(const char* lightname, const glm::vec3& color);
	void setSpecularColor(const char* lightname, float red, float green, float blue);
	void setSpecularColor(const std::string& lightname, const glm::vec3& color);
	void setSpecularColor(const std::string& lightname, float red, float green, float blue);

	//修改方向
	void setDirection(int index, const glm::vec3& dir);
	void setDirection(int index, float x, float y, float z);
	void setDirection(Light* light, const glm::vec3& dir);
	void setDirection(Light* light, float x, float y, float z);
	void setDirection(const char* lightname, const glm::vec3& dir);
	void setDirection(const char* lightname, float x, float y, float z);
	void setDirection(const std::string& lightname, const glm::vec3& dir);
	void setDirection(const std::string& lightname, float x, float y, float z);
	//修改位置
	void setPosition(int index, const glm::vec3& pos);
	void setPosition(int index, float x, float y, float z);
	void setPosition(Light* light, const glm::vec3& pos);
	void setPosition(Light* light, float x, float y, float z);
	void setPosition(const char* lightname, const glm::vec3& pos);
	void setPosition(const char* lightname, float x, float y, float z);
	void setPosition(const std::string& lightname, const glm::vec3& pos);
	void setPosition(const std::string& lightname, float x, float y, float z);
	//修改点光级别，点光级别即为点光强度
	void setPointLightLevel(int index, float level);
	void setPointLightLevel(Light* light, float level);
	void setPointLightLevel(const char* lightname, float level);
	void setPointLightLevel(std::string& lightname, float level);
	//修改聚光角度
	void setSpotLightCutOff(int index, float inCut, float outerCut);
	void setSpotLightCutOff(Light* light, float inCut, float outerCut);
	void setSpotLightCutOff(const char* lightname, float inCut, float outerCut);
	void setSpotLightCutOff(const std::string& lightname, float inCut, float outerCut);

	//获取光照信息
	//获取环境光返回环境光或NULL
	Light* getAmbientLight();
	//获取点光，返回带有点光数据的vector
	std::vector<Light*> getPointLight();
	//获取聚光，返回带有聚光数据的vector
	std::vector<Light*> getSpotLight();

	//工具方法 获取索引
	int getLightIndex(Light* l);
	int getLightIndex(const char* lightname);
	int getLightIndex(const std::string& lightname);

	//光照步进
	void step();
	//光照绘图
	void draw();
private:
};
#endif