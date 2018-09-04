#include "glDemo.h"
#include "AppWindow.h"
#include "utils/log.h"

#include<iostream>

const char * const glDemoApp::APP_NAME = APPLICATION_NAME;

glDemoApp::glDemoApp(){

}

glDemoApp::~glDemoApp() {

}

int glDemoApp::init() {
	//Init Log
	Log::initMessage();

	//Init window
	_window = new AppWindow();

	if (_window->initGLWindow() != AppWindow::InitCode::success) {
		Log::log(GLDEMO_MES_WINDOW_INIT_FAIL);
		return -1;
	}

	return 0;
}

void glDemoApp::run() {
	if(init()!=0)
		return;

	_window->loop();
}