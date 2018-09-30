#include "light.h"
#include "properties/shader.h"
#include <glm/glm.hpp>

Light::Light(Stage *s):Object(s),_ambient(1.0f, 1.0f, 1.0f), _diffuse(1.0f, 1.0f, 1.0f), _specular(1.0f, 1.0f, 1.0f),
_direction(0.0f), _constant(1.0f), _linear(1.0f), _quadratic(1.0f),
_cutOff(14.0f), _outerCutOff(17.0f), _type(LightManager::type::unset) {
	
}

void Light::setPosition(float x, float y, float z) {
	_position.x = x;
	_position.y = y;
	_position.z = z;
}
void Light::setPosition(const glm::vec3& pos) {
	_position = pos;
}
void Light::setDirection(float x, float y, float z) {
	_direction.x = x;
	_direction.y = y;
	_direction.z = z;
}
void Light::setDirection(const glm::vec3& pos) {
	_direction = pos;
}
void Light::setAmbientColor(float red, float green, float blue) {
	_ambient.r = red;
	_ambient.g = green;
	_ambient.b = blue;
}
void Light::setDiffuseColor(float red, float green, float blue) {
	_diffuse.r = red;
	_diffuse.g = green;
	_diffuse.b = blue;
}
void Light::setSpecularColor(float red, float green, float blue) {
	_specular.r = red;
	_specular.g = green;
	_specular.b = blue;
}
void Light::setConstant(float val) {
	_constant = val;
}
void Light::setLinear(float val) {
	_linear = val;
}
void Light::setQuadratic(float val) {
	_quadratic = val;
}
void Light::setCutOff(float val) {
	_cutOff = glm::cos(glm::radians(val));
}
void Light::setOuterCutOff(float val) {
	_outerCutOff = glm::cos(glm::radians(val));
}

//Formula comes from http://wiki.ogre3d.org/Light+Attenuation+Shortcut
void Light::setPointLightLevel(float level) {
	_constant = 1.0f;
	_linear = 4.5f / level;
	_quadratic = 75.0f / (level * level);
}


vertLight::vertLight(Stage* s, float* vertices, int nvert):Light(s),vertObject(s){
	vertObject::setVertices(vertices, nvert);
}


void vertLight::setPosition(float x, float y, float z) {
	Light::setPosition(x, y, z);
	moveTo(x, y, z);
}

void vertLight::setPosition(const glm::vec3& pos) {
	Light::setPosition(pos);
	moveTo(pos.x, pos.y, pos.z);
}

void vertLight::draw() {
	Entity::draw();
}