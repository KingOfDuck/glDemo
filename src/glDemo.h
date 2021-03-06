#ifndef __GLDEMO_H
#define __GLDEMO_H

#define APPLICATION_NAME "glDemoTest"
#define MAX_FRAME 300
#define DEFAULT_MOUSE_SENSITIVITY 0.1f

//Graphics Mode
#define OPENGL_3_0 0

class AppWindow;
class glDemoApp {
private:
	AppWindow* _window;
	
public:
	static const int APP_GL_VERSION_MAJOR = 3;
	static const int APP_GL_VERSION_MINOR = 3;
	static const char * const APP_NAME;
	static const int MAX_FRAME_SEC = 3600/MAX_FRAME;
	static const int APP_GRAPHICS_MODE = OPENGL_3_0;

private:
	int init();
public:
	glDemoApp();
	~glDemoApp();

	void run();
};
#endif