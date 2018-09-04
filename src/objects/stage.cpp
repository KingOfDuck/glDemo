#include "stage.h"
#include "camera.h"
#include "object.h"

Stage::Stage(AppWindow *w):
	_window(w),_camera(new Camera()),_canvas(new Canvas()){
	
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

void Stage::draw() {
	glEnable(GL_DEPTH_TEST);
	_canvas->draw();
	_camera->step();
}