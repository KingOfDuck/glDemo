#include "AppWindow.h"
#include "glDemo.h"
#include "utils/time.h"
#include "objects/stage.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

AppWindow::AppWindow():
	_clientWidth(800),_clientHeight(600){

}

//Standard Initialization
int AppWindow::initGLWindow() {
	//Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glDemoApp::APP_GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glDemoApp::APP_GL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	//Create Window
	_window = glfwCreateWindow(_clientWidth, _clientHeight, glDemoApp::APP_NAME, NULL, NULL);
	if (_window == NULL) {
		glfwTerminate();
		return InitCode::windowCreateFail;
	}
	glfwMakeContextCurrent(_window);

	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		return InitCode::gladInitFail;
	}
	
	//Set Callbacks
	glfwSetWindowSizeCallback(_window, AppWindow::framebufferSizeCallback);

	//Init stages
	initStage();

	return InitCode::success;
}

//window loop
//In each loop, window first call stages to draw
//after stages done all the steps, the buffer is ready and then swapbuffers
void AppWindow::loop() {
	int t;
	while (!glfwWindowShouldClose(_window)) {
		Time::Step();
		t = Time::DeltaTime() * 1000;
		if (t < glDemoApp::MAX_FRAME_SEC) {
			Sleep(glDemoApp::MAX_FRAME_SEC - t);
		}

		glfwPollEvents();

		_stage->step();

		glfwSwapBuffers(_window);
	}
}


//STATIC CALLBACK FUNCTION
//called when windows size has changed
void AppWindow::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}