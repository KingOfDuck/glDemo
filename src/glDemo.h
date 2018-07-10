#ifndef __GLDEMO_H
#define __GLDEMO_H

#define APPLICATION_NAME "glDemo³ÌÐò"
#define MAX_FRAME 120

class AppWindow;
class glDemoApp {
private:
	AppWindow* _window;
	
public:
	static const int APP_GL_VERSION_MAJOR = 3;
	static const int APP_GL_VERSION_MINOR = 3;
	static const char * const APP_NAME;
	static const int MAX_FRAME_SEC = 3600/MAX_FRAME;

private:
	int init();
public:
	glDemoApp();
	~glDemoApp();

	void run();
};
#endif