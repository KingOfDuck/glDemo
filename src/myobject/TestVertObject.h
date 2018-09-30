#ifndef __TESTVERTOBJECT_H
#define __TESTVERTOBJECT_H

#include "../object/object.h"
#include "../stage/stage.h"
#include "../object/light.h"
#include <glm/vec3.hpp>
#include <vector>

class TestObject : public vertObject {
public:
	TestObject(float*vertices, int nvert, Stage* s);
	///override
	void paint();
	///override
	void step();
private:
	TestObject();
	void init();
};

class TestStage :public Stage {
public:
	TestStage(AppWindow* w);
	void loop();
	void paint();
private:
	TestStage();
	TestStage(TestStage&);
	TestStage(TestStage&&);
	TestStage(TestStage*);

	void _inputProcess();
};

class TestLight : public vertLight {
private:
public:
	TestLight(float* vertices = NULL, int nvert = 0, Stage *s = NULL);
	void paint();
	void step();
private:
	void init();
	TestLight();
};

#endif