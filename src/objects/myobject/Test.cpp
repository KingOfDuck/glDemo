#include "TestObject.h"
#include "TestStage.h"
#include "../../AppWindow.h"


void AppWindow::initStage() {
	_stage = new TestStage(this);
}

TestStage::TestStage(AppWindow *w) :
	Stage(w) {
	//TODO: Init Objects;
}

void TestStage::step() {
	//Step is divided into two parts: prepare and draw
	//Preparing the informations for drawing: status, movements, textures, lightlings, shaders, ...

	//Clear Screen
	_canvas->draw();

	for (auto i = _objects.begin(); i != _objects.end(); ++i) {
		//TODO: Objects Movement
	}

	//Draw all objects
	for (auto i = _objects.begin(); i != _objects.end(); ++i) {
		_canvas->drawObj(*i);
	}
}