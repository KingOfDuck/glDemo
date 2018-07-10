#include "Time.h"
#include <glfw/glfw3.h>

double Time::_deltatime;
double Time::_time;

void Time::Step() {
	double time = glfwGetTime();
	
	_deltatime = time - _time;
	_time = time;
}

double Time::GetTime() {
	return _time;
}

double Time::DeltaTime() {
	return _deltatime;
}