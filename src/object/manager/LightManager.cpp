#include "LightManager.h"
#include "../light.h"

LightManager::LightManager():_ambientlight(LIGHTM_NODIRLIGHT){
}

//添加灯光
void LightManager::addLight(Light* light, const char* name) {
	_lightmap.insert(std::pair<std::string, int>(name,(int)_lights.size()));

	light->_type = lighttype::unset;

	//先插入空位
	for (auto i = _lights.begin(); i != _lights.end(); i++) {
		if (*i == NULL) {
			*i = light;
			return;
		}
	}

	_lights.push_back(light);
}
void LightManager::addLight(Light* light, const std::string& name) {
	_lightmap.insert(std::pair<std::string, int>(name, (int)_lights.size()));

	light->_type = lighttype::unset;
	//先插入空位
	for (auto i = _lights.begin(); i != _lights.end(); i++) {
		if (*i == NULL) {
			*i = light;
			return;
		}
	}
	_lights.push_back(light);
}

void LightManager::deleteLight(int index) {
	if (index < 0) {
		//TODO:Log 光照索引错误
		return;
	}
	//删除一个灯光后，其索引变成NULL，但仍然占用member空间，type变为deleted
	//从map中移除索引
	for (auto it = _lightmap.begin(); it != _lightmap.end(); it++) {
		if (it->second == index) {
			_lightmap.erase(it);
			break;
		}
	}
	//环境光删除，则场景无环境光
	switch (_lights[index]->_type)
	{
	case lighttype::deleted:
		//TODO: LOG re-delete
		break;
	case lighttype::unset:
		break;
	case lighttype::dir:
		_ambientlight = LIGHTM_NODIRLIGHT;
		break;
	case lighttype::point:
		_npointlight--;
		break;
	case lighttype::spot:
		_nspotlight--;
		break;
	default:
		//TODO: LOG wrong light type
		break;
	}
	_lights[index] = NULL;
}
void LightManager::deleteLight(Light* light) {
	deleteLight(getLightIndex(light));
}
void LightManager::deleteLight(const char* lightname) {
	deleteLight(getLightIndex(lightname));
}
void LightManager::deleteLight(const std::string& lightname) {
	deleteLight(getLightIndex(lightname));
}

void LightManager::setLightType(int index, lighttype type) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	//可设置为环境光，聚光和点光
	switch (type)
	{
	case lighttype::dir:
		if (_ambientlight != -1) {
			if (_lights[_ambientlight] != NULL) {
				_lights[_ambientlight]->_type = lighttype::unset;
			}
		}
		_lights[index]->_type = type;
		_ambientlight = index;
		break;
	case lighttype::point:
		if (_npointlight >= LIGHTM_MAXPOINTLIGHT) {
			//TODO:LOG too many pointlights
			_npointlight++;
		}
		_lights[index]->_type = type;
		break;
	case lighttype::spot:
	case lighttype::cameraspot:
		if (_nspotlight >= LIGHTM_MAXSPOTLIGHT) {
			//TODO:LOG too many spotlights
			_nspotlight++;
		}
		_lights[index]->_type = type;
		break;
	default:
		//TODO: Log 错误的光类型设置
		break;
	}
}
void LightManager::setLightType(Light* light, lighttype type) {
	setLightType(getLightIndex(light),type);
}
void LightManager::setLightType(const char* lightname, lighttype type) {
	setLightType(getLightIndex(lightname), type);
}
void LightManager::setLightType(const std::string& lightname, lighttype type) {
	setLightType(getLightIndex(lightname), type);
}

void LightManager::setAmbientColor(int index, const glm::vec3& color) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	_lights[index]->setAmbientColor(color.x, color.y, color.z);
}
void LightManager::setAmbientColor(int index, float red, float green, float blue) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	_lights[index]->setAmbientColor(red, green, blue);
}
void LightManager::setAmbientColor(Light* light, const glm::vec3& color) {
	light->setAmbientColor(color.x, color.y, color.z);
}
void LightManager::setAmbientColor(Light* light, float red, float green, float blue) {
	light->setAmbientColor(red, green, blue);
}
void LightManager::setAmbientColor(const char* lightname, const glm::vec3& color) {
	setAmbientColor(getLightIndex(lightname), color);
}
void LightManager::setAmbientColor(const char* lightname, float red, float green, float blue) {
	setAmbientColor(getLightIndex(lightname), red, green, blue);
}
void LightManager::setAmbientColor(const std::string& lightname, const glm::vec3& color){
	setAmbientColor(getLightIndex(lightname), color);
}
void LightManager::setAmbientColor(const std::string& lightname, float red, float green, float blue){
	setAmbientColor(getLightIndex(lightname), red, green, blue);
}


void LightManager::setDiffuseColor(int index, const glm::vec3& color) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	_lights[index]->setDiffuseColor(color.x, color.y, color.z);
}
void LightManager::setDiffuseColor(int index, float red, float green, float blue) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	_lights[index]->setDiffuseColor(red, green, blue);
}
void LightManager::setDiffuseColor(Light* light, const glm::vec3& color) {
	light->setDiffuseColor(color.x, color.y, color.z);
}
void LightManager::setDiffuseColor(Light* light, float red, float green, float blue) {
	light->setDiffuseColor(red, green, blue);
}
void LightManager::setDiffuseColor(const char* lightname, const glm::vec3& color) {
	setDiffuseColor(getLightIndex(lightname), color);
}
void LightManager::setDiffuseColor(const char* lightname, float red, float green, float blue) {
	setDiffuseColor(getLightIndex(lightname), red, green, blue);
}
void LightManager::setDiffuseColor(const std::string& lightname, const glm::vec3& color) {
	setDiffuseColor(getLightIndex(lightname), color);
}
void LightManager::setDiffuseColor(const std::string& lightname, float red, float green, float blue) {
	setDiffuseColor(getLightIndex(lightname), red, green, blue);
}


void LightManager::setSpecularColor(int index, const glm::vec3& color) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	_lights[index]->setSpecularColor(color.x, color.y, color.z);
}
void LightManager::setSpecularColor(int index, float red, float green, float blue) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	_lights[index]->setSpecularColor(red, green, blue);
}
void LightManager::setSpecularColor(Light* light, const glm::vec3& color) {
	light->setSpecularColor(color.x, color.y, color.z);
}
void LightManager::setSpecularColor(Light* light, float red, float green, float blue) {
	light->setSpecularColor(red, green, blue);
}
void LightManager::setSpecularColor(const char* lightname, const glm::vec3& color) {
	setSpecularColor(getLightIndex(lightname), color);
}
void LightManager::setSpecularColor(const char* lightname, float red, float green, float blue) {
	setSpecularColor(getLightIndex(lightname), red, green, blue);
}
void LightManager::setSpecularColor(const std::string& lightname, const glm::vec3& color) {
	setSpecularColor(getLightIndex(lightname), color);
}
void LightManager::setSpecularColor(const std::string& lightname, float red, float green, float blue) {
	setSpecularColor(getLightIndex(lightname), red, green, blue);
}


void LightManager::setDirection(int index, const glm::vec3& dir) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	_lights[index]->setDirection(dir.x, dir.y, dir.z);
}
void LightManager::setDirection(int index, float x, float y, float z) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	_lights[index]->setDirection(x, y, z);
}
void LightManager::setDirection(Light* light, const glm::vec3& dir) {
	light->setDirection(dir.x, dir.y, dir.z);
}
void LightManager::setDirection(Light* light, float x, float y, float z) {
	light->setDirection(x, y, z);
}
void LightManager::setDirection(const char* lightname, const glm::vec3& dir) {
	setDirection(getLightIndex(lightname), dir);
}
void LightManager::setDirection(const char* lightname, float x, float y, float z) {
	setDirection(getLightIndex(lightname), x, y, z);
}
void LightManager::setDirection(const std::string& lightname, const glm::vec3& dir){
	setDirection(getLightIndex(lightname), dir);
}
void LightManager::setDirection(const std::string& lightname, float x, float y, float z){
	setDirection(getLightIndex(lightname), x, y, z);
}

void LightManager::setPosition(int index, const glm::vec3& pos) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	_lights[index]->setPosition(pos.x, pos.y, pos.z);
}
void LightManager::setPosition(int index, float x, float y, float z) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	_lights[index]->setPosition(x, y, z);
}
void LightManager::setPosition(Light* light, const glm::vec3& pos) {
	light->setPosition(pos.x, pos.y, pos.z);
}
void LightManager::setPosition(Light* light, float x, float y, float z) {
	light->setPosition(x, y, z);
}
void LightManager::setPosition(const char* lightname, const glm::vec3& pos) {
	setPosition(getLightIndex(lightname), pos.x, pos.y, pos.z);
}
void LightManager::setPosition(const char* lightname, float x, float y, float z) {
	setPosition(getLightIndex(lightname), x, y, z);
}
void LightManager::setPosition(const std::string& lightname, const glm::vec3& pos){
	setPosition(getLightIndex(lightname), pos.x, pos.y, pos.z);
}
void LightManager::setPosition(const std::string& lightname, float x, float y, float z){
	setPosition(getLightIndex(lightname), x, y, z);
}

void LightManager::setPointLightLevel(int index, float level) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	_lights[index]->setPointLightLevel(level);
}
void LightManager::setPointLightLevel(Light* light, float level) {
	light->setPointLightLevel(level);
}
void LightManager::setPointLightLevel(const char* lightname, float level) {
	setPointLightLevel(getLightIndex(lightname), level);
}
void LightManager::setPointLightLevel(std::string& lightname, float level){
	setPointLightLevel(getLightIndex(lightname), level);
}

void LightManager::setSpotLightCutOff(int index, float inCut, float outerCut) {
	if (index < 0) {
		//TODO:Log 光照删除错误
		return;
	}
	_lights[index]->setCutOff(inCut);
	_lights[index]->setOuterCutOff(outerCut);
}
void LightManager::setSpotLightCutOff(Light* light, float inCut, float outerCut) {
	light->setCutOff(inCut);
	light->setOuterCutOff(outerCut);
}
void LightManager::setSpotLightCutOff(const char* lightname, float inCut, float outerCut) {
	setSpotLightCutOff(getLightIndex(lightname), inCut, outerCut);
}
void LightManager::setSpotLightCutOff(const std::string& lightname, float inCut, float outerCut) {
	setSpotLightCutOff(getLightIndex(lightname), inCut, outerCut);
}

Light* LightManager::getAmbientLight() {
	if (_ambientlight == LIGHTM_NODIRLIGHT)
		return NULL;
	return _lights[_ambientlight];
}

std::vector<Light*> LightManager::getPointLight() {
	std::vector<Light*> lights;
	lights.clear();
	for (int i = 0; i < _lights.size(); ++i) {
		if (_lights[i]->_type == lighttype::point)
			lights.push_back(_lights[i]);
	}
	return lights;
}

std::vector<Light*> LightManager::getSpotLight() {
	std::vector<Light*> lights;
	lights.clear();
	for (int i = 0; i < _lights.size(); ++i) {
		if (_lights[i]->_type == lighttype::spot || _lights[i]->_type == lighttype::cameraspot)
			lights.push_back(_lights[i]);
	}
	return lights;
}

//工具方法 获取索引
int LightManager::getLightIndex(Light* l) {
	for (int i = 0; i < _lights.size(); i++) {
		if (_lights[i] == l) {
			return i;
		}
	}
	return -1;
}
int LightManager::getLightIndex(const char* lightname) {
	int i = 0;
	for (auto it = _lightmap.begin(); it != _lightmap.end(); it++) {
		if (it->first == lightname) {
			return i;
		}
		i++;
	}
	return -1;
}
int LightManager::getLightIndex(const std::string& lightname) {
	return getLightIndex(lightname.c_str());
}

void LightManager::step() {
	for (auto i = _lights.begin(); i != _lights.end(); ++i) {
		if ((*i)->_type > lighttype::deleted) {
			(*i)->step();		
		}
	}
}
void LightManager::draw() {
	for (auto i = _lights.begin(); i != _lights.end(); ++i) {
		if ((*i)->_type > lighttype::deleted)
			(*i)->draw();
	}
}