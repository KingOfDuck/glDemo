#define _CRT_SECURE_NO_WARNINGS
#include "shader.h"
#include "../manager/ResourceManager.h"
#include "../light.h"
#include <sstream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <string>

//一个Shader必须同时有顶点、片段两个着色器

//private 构造，copy()使用
Shader::Shader():_id(-1){
}

Shader* Shader::LoadFromFile(const char* vertex, const char* fragment){
	Shader* res = new Shader();
	res->_id = ResourceManager::loadShader(vertex, fragment);
	return res;
}

Shader* Shader::copy() {
	Shader* result = new Shader();
	result->_id = _id;
	return result;
}

void Shader::use() {
	glUseProgram(_id);
}
void Shader::setParameter(int l, int val) {
	glUniform1i(l, val);
}
void Shader::setParameter(int l, glm::mat4 m) {
	glUniformMatrix4fv(l, 1, GL_FALSE, glm::value_ptr(m));
}
void Shader::setParameter(int l, glm::vec3 v) {
	glUniform3fv(l, 1, &v[0]);
}
void Shader::setParameter(int l, float a) {
	glUniform1f(l, a);
}
void Shader::setParameter(int l, bool a) {
	glUniform1i(l, a ? 1 : 0);
}

void Shader::setAmbientLight(Light* light) {
	if (light) {
		setParameter(LIGHT_BOOL_HASDIRLIGHT, true);
		setParameter(std::string(LIGHT_NAME_DIRLIGHT)+ LIGHT_ATTR_DIRECTION, light->getDirection());
		setParameter(std::string(LIGHT_NAME_DIRLIGHT) + LIGHT_ATTR_AMBIENT, light->getAmbientColor());
		setParameter(std::string(LIGHT_NAME_DIRLIGHT) + LIGHT_ATTR_DIFFUSE, light->getDiffuseColor());
		setParameter(std::string(LIGHT_NAME_DIRLIGHT) + LIGHT_ATTR_SPECULAR, light->getSpecularColor());
	}
	else {
		setParameter(LIGHT_BOOL_HASDIRLIGHT, false);
	}
}

void Shader::setPointLight(const std::vector<Light*>& lights) {
	std::string buf;
	char num[6];
	setParameter(LIGHT_NUMBER_POINTLIGHT, (int)lights.size());
	for (int i = 0; i < lights.size(); ++i) {
		buf.clear();
		buf = buf + LIGHT_NAME_POINTLIGHT + "[";
		sprintf(num, "%d\0", i);
		buf += num;
		buf += "]";

		setParameter(buf + LIGHT_ATTR_POSITION,lights[i]->getPosition());
		setParameter(buf + LIGHT_ATTR_CONSTANT, lights[i]->getConstant());
		setParameter(buf + LIGHT_ATTR_LINEAR, lights[i]->getLinear());
		setParameter(buf + LIGHT_ATTR_QUADRATIC, lights[i]->getQuadratic());
		setParameter(buf + LIGHT_ATTR_AMBIENT,lights[i]->getAmbientColor());
		setParameter(buf + LIGHT_ATTR_DIFFUSE, lights[i]->getDiffuseColor());
		setParameter(buf + LIGHT_ATTR_SPECULAR, lights[i]->getSpecularColor());
	}
}

void Shader::setSpotLight(const std::vector<Light*>& lights) {
	std::string buf;
	char num[6];
	setParameter(LIGHT_NUMBER_SPOTLIGHT, (int)lights.size());
	for (int i = 0; i < lights.size(); ++i) {
		buf.clear();
		buf = buf + LIGHT_NAME_SPOTLIGHT + "[";
		sprintf(num, "%d\0", i);
		buf += num;
		buf += "]";
		
		if (lights[i]->isCameraSpot()) {
			setParameter(buf + LIGHT_ATTR_ISCAMERASPOT, true);
		}
		else {
			setParameter(buf + LIGHT_ATTR_ISCAMERASPOT, false);
			setParameter(buf + LIGHT_ATTR_POSITION, lights[i]->getPosition());
			setParameter(buf + LIGHT_ATTR_DIRECTION, lights[i]->getDirection());
		}
		setParameter(buf + LIGHT_ATTR_CONSTANT, lights[i]->getConstant());
		setParameter(buf + LIGHT_ATTR_LINEAR, lights[i]->getLinear());
		setParameter(buf + LIGHT_ATTR_QUADRATIC, lights[i]->getQuadratic());
		setParameter(buf + LIGHT_ATTR_AMBIENT, lights[i]->getAmbientColor());
		setParameter(buf + LIGHT_ATTR_DIFFUSE, lights[i]->getDiffuseColor());
		setParameter(buf + LIGHT_ATTR_SPECULAR, lights[i]->getSpecularColor());
		setParameter(buf + LIGHT_ATTR_CUTOFF, lights[i]->getCutOff());
		setParameter(buf + LIGHT_ATTR_OUTERCUTOFF, lights[i]->getOuterCutOff());
	}
}

Shader::~Shader() {
	ResourceManager::removeShader(_id);
}