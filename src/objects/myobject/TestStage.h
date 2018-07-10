#ifndef __TESTSTAGE_H
#define __TESTSTAGE_H

#include "../stage.h"

class TestStage :public Stage {
public:
	TestStage(AppWindow* w);
	void step();
private:
	TestStage();
	TestStage(TestStage&); 
	TestStage(TestStage&&);
	TestStage(TestStage*);
};
#endif
