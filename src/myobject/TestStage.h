#ifndef __TESTSTAGE_H
#define __TESTSTAGE_H

#include "../stage/stage.h"

class TestStage :public Stage {
public:
	TestStage(AppWindow* w);
	void step();
	void draw();
private:
	TestStage();
	TestStage(TestStage&); 
	TestStage(TestStage&&);
	TestStage(TestStage*);

	void _inputProcess();
};
#endif
