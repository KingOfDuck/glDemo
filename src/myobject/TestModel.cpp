#include "../AppWindow.h"
#include "../utils/time.h"
#include "../stage/camera.h"
#include "../object/Model.h"
#include "TestModel.h"
#include <glfw/glfw3.h>

//Stage
void AppWindow::initStage() {
	_stage = new TestModelStage(this);
}



TestModelStage::TestModelStage(AppWindow *w) :
	Stage(w) {
	_canvas = new Canvas(0.0f,0.0f,0.0f);
	_camera = new Camera();
	setPerspective(45.0f, (float)w->getClientWidth() / (float)w->getClientHeight(), 0.1f, 100.0f);
	//Add Objects
	Model *model = new Model("res/model/nanosuit/nanosuit.obj",this);
	model->scaleTo(0.3f, 0.3f, 0.3f);
	_objects.push_back(model);
	//Add Lights
	_lightmanager.addLight(new TestModelLight(), "ambient");
	_lightmanager.setLightType(0, LightManager::type::dir);
	_lightmanager.setPosition(0, -4.0f, 1.2f, -8.0f);
	_lightmanager.setDirection(0, -0.2f, -1.0f, -0.3f);
	_lightmanager.setAmbientColor(0, 0.05f, 0.05f, 0.05f);
	_lightmanager.setDiffuseColor(0, 0.4f, 0.4f, 0.4f);
	_lightmanager.setSpecularColor(0, 0.5f, 0.5f, 0.5f);


	_lightmanager.addLight(new TestModelLight(), "p0");
	_lightmanager.setLightType(1, LightManager::type::point);
	_lightmanager.setPosition(1, 0.7f, 0.2f, 2.0f);
	_lightmanager.setAmbientColor(1, 0.05f, 0.05f, 0.05f);
	_lightmanager.setDiffuseColor(1, 0.8f, 0.8f, 0.8f);
	_lightmanager.setSpecularColor(1, 1.0f, 1.0f, 1.0f);
	_lightmanager.setPointLightLevel(1, 50);

	_lightmanager.addLight(new TestModelLight(), "p1");
	_lightmanager.setLightType(2, LightManager::type::point);
	_lightmanager.setPosition(2, 2.3f, -3.3f, -4.0f);
	_lightmanager.setAmbientColor(2, 0.05f, 0.05f, 0.05f);
	_lightmanager.setDiffuseColor(2, 0.8f, 0.8f, 0.8f);
	_lightmanager.setSpecularColor(2, 1.0f, 1.0f, 1.0f);
	_lightmanager.setPointLightLevel(2, 50);

	_lightmanager.addLight(new TestModelLight(), "p2");
	_lightmanager.setLightType(3, LightManager::type::point);
	_lightmanager.setPosition(3, -4.0f, 2.0f, -12.0f);
	_lightmanager.setAmbientColor(3, 0.05f, 0.05f, 0.05f);
	_lightmanager.setDiffuseColor(3, 0.8f, 0.8f, 0.8f);
	_lightmanager.setSpecularColor(3, 1.0f, 1.0f, 1.0f);
	_lightmanager.setPointLightLevel(3, 50);

	_lightmanager.addLight(new TestModelLight(), "p3");
	_lightmanager.setLightType(4, LightManager::type::point);
	_lightmanager.setPosition(4, 0.0f, 0.0f, -3.0f);
	_lightmanager.setAmbientColor(4, 0.05f, 0.05f, 0.05f);
	_lightmanager.setDiffuseColor(4, 0.8f, 0.8f, 0.8f);
	_lightmanager.setSpecularColor(4, 1.0f, 1.0f, 1.0f);
	_lightmanager.setPointLightLevel(4, 50);

	_lightmanager.addLight(new TestModelLight(), "s1");
	_lightmanager.setLightType(5, LightManager::type::cameraspot);
	_lightmanager.setAmbientColor(5, 0.0f, 0.0f, 0.0f);
	_lightmanager.setDiffuseColor(5, 1.0f, 1.0f, 1.0f);
	_lightmanager.setSpecularColor(5, 1.0f, 1.0f, 1.0f);
	_lightmanager.setPointLightLevel(5, 50);
	_lightmanager.setSpotLightCutOff(5, 10.5f, 17.0f);
}

void TestModelStage::_inputProcess() {
	//Keyboards
	bool* keys = _window->getKeys();
	if (keys[GLFW_KEY_W]) {
		_camera->moveFront((float)Time::DeltaTime());
	}
	else if (keys[GLFW_KEY_S]) {
		_camera->moveFront((float)-Time::DeltaTime());
	}

	if (keys[GLFW_KEY_A]) {
		_camera->moveLeft((float)Time::DeltaTime());
	}
	else if (keys[GLFW_KEY_D]) {
		_camera->moveLeft(-(float)Time::DeltaTime());
	}

	if (keys[GLFW_KEY_ESCAPE]) {
		_window->close();
	}
	//Mouse
	const MouseEvent &e = _window->getMouseEvent();//Cannot be changed
	if (e._dirty) {
		if (e._keys[GLFW_MOUSE_BUTTON_LEFT])
			_camera->rotate(e._offsety, e._offsetx);
	}

}
void TestModelStage::loop() {
	//Step is divided into two parts: prepare and draw
	_inputProcess();
}


//Light
TestModelLight::TestModelLight(Stage *s) :Light(s), Object(s) {
}
