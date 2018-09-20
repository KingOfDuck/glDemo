#define _CRT_SECURE_NO_WARNINGS
#include "shader.h"
#include "../manager/ShaderManager.h"
#include "../light.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

//一个Shader必须同时有顶点、片段两个着色器

//private 构造，copy()使用
Shader::Shader():_id(-1){
}
Shader::Shader(const char* vertex, const char* fragment){
	loadFromFile(vertex, fragment);
}
void Shader::loadFromFile(const char* vertex, const char* fragment) {
	_id = ShaderManager::load(vertex, fragment);
}
Shader* Shader::copy() {
	Shader* result = new Shader();
	result->_id = _id;
	return result;
}

void Shader::use() {
	glUseProgram(_id);
}
void Shader::setParameter(const char* name, int val) {
	int l = glGetUniformLocation(_id, name);
	glUniform1i(l, val);
}
void Shader::setParameter(const char* name, const glm::mat4 &m) {
	int l = glGetUniformLocation(_id, name);
	glUniformMatrix4fv(l, 1, GL_FALSE, glm::value_ptr(m));
}
void Shader::setParameter(const char* name, const glm::vec3 &v) {
	int l = glGetUniformLocation(_id, name);
	glUniform3fv(l, 1, &v[0]);
}
void Shader::setParameter(const char* name, float a) {
	int l = glGetUniformLocation(_id, name);
	glUniform1f(l, a);
}
void Shader::setParameter(const char* name, bool a) {
	int l = glGetUniformLocation(_id, name);
	glUniform1i(l, a ? 1 : 0);
}
template <typename T>
void Shader::setParameter(const std::string& str, T val) {
	setParameter(str.c_str(), val);
}

void Shader::setAmbientLight(Light* light) {
	if (light) {
		setParameter("hasdirlight", true);
		setParameter("dirLight.direction", light->getDirection());
		setParameter("dirLight.ambient", light->getAmbientColor());
		setParameter("dirLight.diffuse", light->getDiffuseColor());
		setParameter("dirLight.specular", light->getSpecularColor());
	}
	else {
		setParameter("hasdirlight", false);
	}
}

void Shader::setPointLight(const std::vector<Light*>& lights) {
	std::string buf;
	char num[6];
	setParameter("npointlight", (int)lights.size());
	for (int i = 0; i < lights.size(); ++i) {
		buf.clear();
		buf += "pointLights[";
		sprintf(num, "%d\0", i);
		buf += num;
		buf += "]";

		setParameter(buf + ".position",lights[i]->getPosition());
		setParameter(buf + ".constant", lights[i]->getConstant());
		setParameter(buf + ".linear", lights[i]->getLinear());
		setParameter(buf + ".quadratic", lights[i]->getQuadratic());
		setParameter(buf + ".ambient",lights[i]->getAmbientColor());
		setParameter(buf + ".diffuse", lights[i]->getDiffuseColor());
		setParameter(buf + ".specular", lights[i]->getSpecularColor());
	}
}

void Shader::setSpotLight(const std::vector<Light*>& lights) {
	std::string buf;
	char num[6];
	setParameter("nspotlight", (int)lights.size());
	for (int i = 0; i < lights.size(); ++i) {
		buf.clear();
		buf += "spotLights[";
		sprintf(num, "%d\0", i);
		buf += num;
		buf += "]";
		
		if (lights[i]->isCameraSpot()) {
			setParameter(buf + ".cameraSpot", 1);
		}
		else {
			setParameter(buf + ".cameraSpot", 0);
			setParameter(buf + ".position", lights[i]->getPosition());
			setParameter(buf + ".constant", lights[i]->getConstant());
		}
		setParameter(buf + ".constant", lights[i]->getConstant());
		setParameter(buf + ".linear", lights[i]->getLinear());
		setParameter(buf + ".quadratic", lights[i]->getQuadratic());
		setParameter(buf + ".ambient", lights[i]->getAmbientColor());
		setParameter(buf + ".diffuse", lights[i]->getDiffuseColor());
		setParameter(buf + ".specular", lights[i]->getSpecularColor());
		setParameter(buf + ".cutOff", lights[i]->getCutOff());
		setParameter(buf + ".outerCutOff", lights[i]->getOuterCutOff());
	}
}

Shader::~Shader() {
	ShaderManager::remove(_id);
}