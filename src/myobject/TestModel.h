#ifndef __TESTMODEL_H
#define __TESTMODEL_H

#include "../stage/stage.h"
#include "../object/light.h"
#include <glm/vec3.hpp>
#include <vector>

class TestModelStage :public Stage {
public:
	TestModelStage(AppWindow* w);
	void loop();
	void paint(){}
private:
	TestModelStage();
	TestModelStage(TestModelStage&);
	TestModelStage(TestModelStage&&);
	TestModelStage(TestModelStage*);

	void _inputProcess();
};

class TestModelLight:public Light {
private:
public:
	TestModelLight(Stage *s = NULL);
	void draw(){}
	void paint(){}
	void step() {}
private:
};

#endif
