#ifndef __APPWINDOW_H
#define __APPWINDOW_H

struct GLFWwindow; 
class glDemoApp;
class Stage;

struct MouseEvent {
	float _lastx, _lasty;//mouse position
	bool _firstinput;//first mouse input
					 //if mouse leave the window or enter the window, firstinput = true
	float _offsetx, _offsety;
	float _mouseSense;//mouse sensitivity
	
	bool _dirty;//mouse moved
	//if moved, dirty = true

	bool _keys[8];//mouse button
};

class AppWindow {
	friend class glDemoApp;//only glDemoApp can use _window
private:
	int _clientWidth;
	int _clientHeight;
	
	//Input Parameters
	bool _key[512];//keyboard keys
	MouseEvent _mouse;

	GLFWwindow* _window;
	Stage *_stage;//A window may consists of different stages, and may use several stages at the same time, e.g. spilt window
		//In demo, only one stage is used. TODO: Multiple Stages

	static AppWindow *currentWindow;//Recording the current useing window, for keys and events.

private:
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mousePosCallback(GLFWwindow * window, double x, double y);
	static void mouseEnterCallback(GLFWwindow * window, int entered);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	
	//Customize init stage, Must be defined
	//自定义stage初始化，必须手动定义
	void initStage();
public:
	enum InitCode {
		success,
		windowCreateFail,
		gladInitFail
	};
	AppWindow();
	int initGLWindow();

	inline int getClientWidth() {
		return _clientWidth;
	}
	inline int getClientHeight() {
		return _clientHeight;
	}
	inline float getOffsetX() { return _mouse._offsetx; }
	inline float getOffsetY() { return _mouse._offsety; }
	inline MouseEvent& getMouseEvent() { return _mouse; }
	inline bool *getKeys() { return _key; }
	inline AppWindow* getCurrentWindow() { return currentWindow; }
	

	void close();
	void use();
	void loop();
		
};

#endif