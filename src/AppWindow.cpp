#include "AppWindow.h"
#include "glDemo.h"

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
	
	glfwSetWindowSizeCallback(_window, AppWindow::framebufferSizeCallback);

	return InitCode::success;
}

//window loop, after drawing as well as\
 doing other things, swap buffers and then poll events
int AppWindow::loop() {
	glfwSwapBuffers(_window);
	glfwPollEvents();
}


//STATIC CALLBACK FUNCTION
void AppWindow::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}