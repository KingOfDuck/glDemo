#ifndef __TIME_H
#define __TIME_H

class Time {
private:
	static double _time;
	static double _deltatime;
public:
	static inline double GetTime() { return _time; }
	static inline double DeltaTime() { return _deltatime; }
	static void Step();
};
#endif