#ifndef __TESTSTAGE_H
#define __TESTSTAGE_H

#include "../stage/stage.h"

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
#endif
