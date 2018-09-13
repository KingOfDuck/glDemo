#ifndef __TESTLIGHT_H
#define __TESTLIGHT_H

#include "../object/light.h"

class TestLight : public Light {
private:
public:
	TestLight(float* vertices = NULL, int nvert = 0, Stage *s = NULL);
	void draw();
	void step();
	void init();
private:
	TestLight();
};

#endif