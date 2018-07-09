#ifndef __APPWINDOW_H
#define __APPWINDOW_H
#endif

class GLFWwindow; 
class glDemoApp;

class AppWindow {
	friend class glDemoApp;//only glDemoApp can use _window
private:
	int _clientWidth;
	int _clientHeight;
	GLFWwindow* _window;

private:
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
public:
	AppWindow();
	enum InitCode {
		success,
		windowCreateFail,
		gladInitFail
	};
	int initGLWindow();
	int loop();
};