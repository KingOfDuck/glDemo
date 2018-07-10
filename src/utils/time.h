#ifndef __TIME_H
#define __TIME_H

class Time {
private:
	static double _time;
	static double _deltatime;
public:
	static double GetTime();
	static double DeltaTime();
	static void Step();
};
#endif