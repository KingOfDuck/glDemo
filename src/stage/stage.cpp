#include "stage.h"
#include "camera.h"
#include "../object/object.h"
#include "../object/light.h"
#include <glm/gtc/matrix_transform.hpp>

Stage::Stage(AppWindow *w):
	_window(w),_camera(new Camera()),_canvas(new Canvas()),
	_projection(glm::mat4(1.0f)),_indexAmbientLight(-1){
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

void Stage::setPerspective(float fov, float ar, float n, float f) {
	_projection = glm::perspective(fov,ar,n,f);
}
void Stage::draw() {
	glEnable(GL_DEPTH_TEST);
	_canvas->draw();
	_camera->step();
}

void Stage::setAmbient(int n, float strength) {
	_lights[n]->setAmbient(true, strength);
	_indexAmbientLight = n;
}

void Stage::setAmbient(Light *l, float strength) {
	for (int i = 0; i < _lights.size(); ++i) {
		if (_lights[i] == l) {
			_lights[i]->setAmbient(true, strength);
			_indexAmbientLight = i;
			return;
		}
	}
	//LOG WARNING: Can not find light in the stage
}