#include "Time.h"
#include <glfw/glfw3.h>

double Time::_deltatime = 0.0;
double Time::_time = 0.0;

void Time::Step() {
	double time = glfwGetTime();
	
	_deltatime = time - _time;
	_time = time;
}