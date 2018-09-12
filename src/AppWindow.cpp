#include "AppWindow.h"
#include "glDemo.h"
#include "utils/time.h"
#include "objects/stage.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

AppWindow *AppWindow::currentWindow;

AppWindow::AppWindow():
	_clientWidth(800), _clientHeight(600){
	_mouse._dirty = false;
	_mouse._firstinput = true;
	_mouse._lastx = _mouse._lasty = 0.0f;
	_mouse._mouseSense = DEFAULT_MOUSE_SENSITIVITY;
	_mouse._offsetx = _mouse._offsety = 0.0f;
	for (int i = 0; i < 8; ++i) {
		_mouse._keys[i] = false;
	}

	for (int i = 0; i < 512; ++i) {
		_key[i] = false;
	}
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
	
	return InitCode::success;
}

//window loop
//In each loop, window first call stages to draw
//after stages done all the steps, the buffer is ready and then swapbuffers
void AppWindow::loop() {
	while (!glfwWindowShouldClose(_window)) {
		Time::Step();
		int t = ((int)Time::DeltaTime()) * 1000;
		if (t < glDemoApp::MAX_FRAME_SEC) {
			Sleep(glDemoApp::MAX_FRAME_SEC - t);
		}

		glfwPollEvents();
		_stage->step();

		_stage->draw();

		//鼠标消息修改不放在stage中，而在window中，避免意外，stage只读取数据
		//每一个循环后检查鼠标状态，如果没有移动，设置为false
		if (_mouse._dirty) {
			_mouse._dirty = false;
			_mouse._offsetx = _mouse._offsety = 0.0f;
		}

		glfwSwapBuffers(_window);
	}
}

void AppWindow::use() {
	currentWindow = this;

	glfwMakeContextCurrent(_window);
	//Set Callbacks
	glfwSetWindowSizeCallback(_window, AppWindow::framebufferSizeCallback);
	glfwSetKeyCallback(_window, AppWindow::keyCallback);
	glfwSetCursorPosCallback(_window, AppWindow::mousePosCallback);
	glfwSetCursorEnterCallback(_window, AppWindow::mouseEnterCallback);
	glfwSetMouseButtonCallback(_window, AppWindow::mouseButtonCallback);

	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
	}

	//Init stages
	initStage();
}

void AppWindow::close() {
	glfwSetWindowShouldClose(_window, true);
}

//STATIC CALLBACK FUNCTION
//called when windows size has changed
void AppWindow::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void AppWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		currentWindow->_key[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		currentWindow->_key[key] = false;
	}
}

void AppWindow::mousePosCallback(GLFWwindow * window, double x, double y) {
	MouseEvent &e = currentWindow->getMouseEvent();
	if (e._firstinput) {
		e._firstinput = false;
		e._offsetx = 0.0f;
		e._offsety = 0.0f;
	}
	else {
		e._offsetx = -(e._lastx - (float)x) * e._mouseSense;
		e._offsety = (e._lasty - (float)y) * e._mouseSense;
		e._dirty = true;
	}
	e._lastx = (float)x;
	e._lasty = (float)y;
}
void AppWindow::mouseEnterCallback(GLFWwindow * window, int entered) {
	MouseEvent &e = currentWindow->getMouseEvent();
	e._firstinput = true;
}

void AppWindow::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	MouseEvent &e = currentWindow->getMouseEvent();
	if (action == GLFW_PRESS) {
		e._keys[button] = true;
	}
	else if (action == GLFW_RELEASE) {
		e._keys[button] = false;
	}
}