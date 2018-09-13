#include "light.h"

Light::Light(float* vertices, int nvert, Stage *s):drawObject(s){
	_vertices = vertices;
	_nvert = nvert;
}

void Light::setColor(float r, float g, float b) {
	this->_lightColor = glm::vec3(r, g, b);
}

void Light::setAmbient(bool f,float stren) {
	if (!f) {
		_ambient = 0.0f;
	}
	else {
		if (!_stage) {

		}
		else {
			//LOG warning: This Light do not have a stage
		}
		_ambient = stren;
	}
}