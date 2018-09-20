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
 * ���չ�����
 * �ṩ�ӿڣ�
	��ӹ���
	�޸Ĺ���
	ɾ������
	�趨�������ͣ������⣬�۹⣬��⣬��ʹ�ã�
	��ȡ������Ϣ�������⣬�۹⣬��⣩
 * ��������������С��1
 * �۹�����ÿ����ͷʹ��һ������ϣ���
 * ���ӵ�����������MAXPOINTLIGHT��
 */
class LightManager {
public:
	enum lighttype {
		unset,
		deleted,
		dir,//������
		point,//���Դ
		spot,//�۹�
		cameraspot,//��һ�˳ƾ۹�
	};
private:
	std::map<std::string, int> _lightmap;//map��������Light����
	std::vector<Light*> _lights;//_lights���ʵ�ʵƹ��Ա
	int _ambientlight;//����������
	int _nspotlight;//�۹�Դ����
	int _npointlight;//���Դ����

public:
	LightManager();

	inline const Light* getLight(int index) { 
		if(index >=0 && index < _lights.size())
			return _lights[index]; 
		return NULL;
	}
	//��ӵƹ�
	void addLight(Light* light, const char* name = NULL);
	void addLight(Light* light, const std::string& name = std::string());

	//IDɾ���ƹ�
	void deleteLight(int index);
	//��ַɾ���ƹ�
	void deleteLight(Light* light);
	//������ɾ���ƹ�
	void deleteLight(const char* lightname);
	//������ɾ���ƹ�
	void deleteLight(const std::string& lightname);

	//Id���õƹ�����
	void setLightType(int index, lighttype type);
	//��ַ���õƹ�����
	void setLightType(Light* light, lighttype type);
	//���������õƹ�����
	void setLightType(const char* lightname, lighttype type);
	//���������õƹ�����
	void setLightType(const std::string& lightname, lighttype type);

	//�޸Ĺ�����Ϣ
	//�޸Ļ�������ɫ
	void setAmbientColor(int index, const glm::vec3& color);
	void setAmbientColor(int index, float red, float green, float blue);
	void setAmbientColor(Light* light, const glm::vec3& color);
	void setAmbientColor(Light* light, float red, float green, float blue);
	void setAmbientColor(const char* lightname, const glm::vec3& color);
	void setAmbientColor(const char* lightname, float red, float green, float blue);
	void setAmbientColor(const std::string& lightname, const glm::vec3& color);
	void setAmbientColor(const std::string& lightname, float red, float green, float blue);
	//�޸����������ɫ
	void setDiffuseColor(int index, const glm::vec3& color);
	void setDiffuseColor(int index, float red, float green, float blue);
	void setDiffuseColor(Light* light, const glm::vec3& color);
	void setDiffuseColor(Light* light, float red, float green, float blue);
	void setDiffuseColor(const char* lightname, const glm::vec3& color);
	void setDiffuseColor(const char* lightname, float red, float green, float blue);
	void setDiffuseColor(const std::string& lightname, const glm::vec3& color);
	void setDiffuseColor(const std::string& lightname, float red, float green, float blue);
	//�޸ĸ߹���ɫ
	void setSpecularColor(int index, const glm::vec3& color);
	void setSpecularColor(int index, float red, float green, float blue);
	void setSpecularColor(Light* light, const glm::vec3& color);
	void setSpecularColor(Light* light, float red, float green, float blue);
	void setSpecularColor(const char* lightname, const glm::vec3& color);
	void setSpecularColor(const char* lightname, float red, float green, float blue);
	void setSpecularColor(const std::string& lightname, const glm::vec3& color);
	void setSpecularColor(const std::string& lightname, float red, float green, float blue);

	//�޸ķ���
	void setDirection(int index, const glm::vec3& dir);
	void setDirection(int index, float x, float y, float z);
	void setDirection(Light* light, const glm::vec3& dir);
	void setDirection(Light* light, float x, float y, float z);
	void setDirection(const char* lightname, const glm::vec3& dir);
	void setDirection(const char* lightname, float x, float y, float z);
	void setDirection(const std::string& lightname, const glm::vec3& dir);
	void setDirection(const std::string& lightname, float x, float y, float z);
	//�޸�λ��
	void setPosition(int index, const glm::vec3& pos);
	void setPosition(int index, float x, float y, float z);
	void setPosition(Light* light, const glm::vec3& pos);
	void setPosition(Light* light, float x, float y, float z);
	void setPosition(const char* lightname, const glm::vec3& pos);
	void setPosition(const char* lightname, float x, float y, float z);
	void setPosition(const std::string& lightname, const glm::vec3& pos);
	void setPosition(const std::string& lightname, float x, float y, float z);
	//�޸ĵ�⼶�𣬵�⼶��Ϊ���ǿ��
	void setPointLightLevel(int index, float level);
	void setPointLightLevel(Light* light, float level);
	void setPointLightLevel(const char* lightname, float level);
	void setPointLightLevel(std::string& lightname, float level);
	//�޸ľ۹�Ƕ�
	void setSpotLightCutOff(int index, float inCut, float outerCut);
	void setSpotLightCutOff(Light* light, float inCut, float outerCut);
	void setSpotLightCutOff(const char* lightname, float inCut, float outerCut);
	void setSpotLightCutOff(const std::string& lightname, float inCut, float outerCut);

	//��ȡ������Ϣ
	//��ȡ�����ⷵ�ػ������NULL
	Light* getAmbientLight();
	//��ȡ��⣬���ش��е�����ݵ�vector
	std::vector<Light*> getPointLight();
	//��ȡ�۹⣬���ش��о۹����ݵ�vector
	std::vector<Light*> getSpotLight();

	//���߷��� ��ȡ����
	int getLightIndex(Light* l);
	int getLightIndex(const char* lightname);
	int getLightIndex(const std::string& lightname);

	//���ղ���
	void step();
	//���ջ�ͼ
	void draw();
private:
};
#endif