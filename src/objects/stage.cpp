#include "stage.h"
#include "camera.h"
#include "object.h"
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

void Stage::setPerspective(float fov, float ar, float n, float f) {
	_projection = glm::perspective(fov,ar,n,f);
}

glm::mat4& Stage::getView() {
	return _camera->getViewMatrix();
}

void Stage::draw() {
	glEnable(GL_DEPTH_TEST);
	_canvas->draw();
	_camera->step();
}