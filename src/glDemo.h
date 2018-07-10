#ifndef __GLDEMO_H
#define __GLDEMO_H

#define APPLICATION_NAME "glDemo³ÌÐò"

class AppWindow;
class glDemoApp {
private:
	AppWindow* _window;
	
public:
	static const int APP_GL_VERSION_MAJOR = 3;
	static const int APP_GL_VERSION_MINOR = 3;
	static const char * const APP_NAME;

private:
	int init();
public:
	glDemoApp();
	~glDemoApp();

	void run();
};
#endif