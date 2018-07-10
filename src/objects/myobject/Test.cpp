#include "TestObject.h"
#include "TestStage.h"
#include "../../AppWindow.h"


void AppWindow::initStage() {
	_stage = new TestStage(this);
}

TestStage::TestStage(AppWindow *w) :
	Stage(w) {

}

void TestStage::step() {

}