#include "stage.h"
#include "camera.h"
#include "../object/object.h"
#include "../object/light.h"
#include <glm/gtc/matrix_transform.hpp>

Stage::Stage(AppWindow *w):
	_window(w),_camera(new Camera()),_canvas(new Canvas()),
	_projection(glm::mat4(1.0f)){
}

Stage::~Stage() {
	for (auto i = _objects.begin(); i != _objects.end(); ++i) {
		delete *i;
		*i = NULL;
	}
	_objects.clear();
	delete _canvas;
	delete _camera;
}

const glm::mat4& Stage::getView(){
	return _camera->getViewMatrix(); 
}
const glm::vec3& Stage::getViewPoint() {
	return _camera->getPosition();
}
const glm::vec3& Stage::getViewDir() {
	return _camera->getDirection();
}

void Stage::setPerspective(float fov, float ar, float n, float f) {
	_projection = glm::perspective(fov,ar,n,f);
}

void Stage::draw() {
	glEnable(GL_DEPTH_TEST);
	_canvas->draw();
	_camera->step();
	_lightmanager.draw();
	for (auto i = _objects.begin(); i != _objects.end(); ++i) {
		(*i)->draw();
	}

	this->paint();
}
void Stage::step() {
	this->loop();

	_lightmanager.step();
	for (auto i = _objects.begin(); i != _objects.end(); ++i) {
		//TODO: Objects Movement
		(*i)->step();
	}
}