#ifndef __APPWINDOW_H
#define __APPWINDOW_H

class GLFWwindow; 
class glDemoApp;
class Stage;

class AppWindow {
	friend class glDemoApp;//only glDemoApp can use _window
private:
	int _clientWidth;
	int _clientHeight;
	GLFWwindow* _window;
	Stage *_stage;//A window may consists of different stages, and may use several stages at the same time, e.g. spilt window
		//In demo, only one stage is used. TODO: Multiple Stages

private:
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	void initStage();//Customize init stage, Must be overwritten
public:
	AppWindow();
	enum InitCode {
		success,
		windowCreateFail,
		gladInitFail
	};
	int initGLWindow();
	inline int getClientWidth() {
		return _clientWidth;
	}
	inline int getClientHeight() {
		return _clientHeight;
	}
	void loop();
};
#endif