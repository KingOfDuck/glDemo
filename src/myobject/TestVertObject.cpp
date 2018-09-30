#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw/glfw3.h>

#include "TestVertObject.h"
#include "../AppWindow.h"
#include "../stage/camera.h"
#include "../object/properties/shader.h"
#include "../object/properties/texture.h"
#include "../object/properties/material.h"
#include "../object/properties/drawer.h"
#include "../utils/time.h"


float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};


TestStage::TestStage(AppWindow *w) :
	Stage(w) {
	//TODO: Init Objects;
	_canvas = new Canvas(0.0f, 0.0f, 0.0f);
	_camera = new Camera();
	setPerspective(45.0f, (float)w->getClientWidth() / (float)w->getClientHeight(), 0.1f, 100.0f);
	
	for (int i = 0; i < 10; ++i) {
		TestObject* t = new TestObject(vertices, 288, this);
		t->moveTo(cubePositions[i].x,cubePositions[i].y,cubePositions[i].z);
		float angle = 20.0f * i;
		t->rotate(angle, glm::vec3(1.0f, 0.3f, 0.5f));
		_objects.push_back(t);
	}

	//Add Lights
	_lightmanager.addLight(new TestLight(vertices, 288), "ambient");
	_lightmanager.setLightType(0, LightManager::type::dir);
	_lightmanager.setPosition(0, -4.0f, 1.2f, -8.0f);
	_lightmanager.setDirection(0, -0.2f, -1.0f, -0.3f);
	_lightmanager.setAmbientColor(0, 0.05f, 0.05f, 0.05f);
	_lightmanager.setDiffuseColor(0, 0.4f, 0.4f, 0.4f);
	_lightmanager.setSpecularColor(0, 0.5f, 0.5f, 0.5f);

	
	_lightmanager.addLight(new TestLight(vertices,288, this), "p0");
	_lightmanager.setLightType(1, LightManager::type::point);
	_lightmanager.setPosition(1, 0.7f, 0.2f, 2.0f);
	_lightmanager.setAmbientColor(1, 0.05f, 0.05f, 0.05f);
	_lightmanager.setDiffuseColor(1, 0.8f, 0.8f, 0.8f);
	_lightmanager.setSpecularColor(1, 1.0f, 1.0f, 1.0f);
	_lightmanager.setPointLightLevel(1, 50);
	
	_lightmanager.addLight(new TestLight(vertices, 288, this), "p1");
	_lightmanager.setLightType(2, LightManager::type::point);
	_lightmanager.setPosition(2, 2.3f, -3.3f, -4.0f);
	_lightmanager.setAmbientColor(2, 0.05f, 0.05f, 0.05f);
	_lightmanager.setDiffuseColor(2, 0.8f, 0.8f, 0.8f);
	_lightmanager.setSpecularColor(2, 1.0f, 1.0f, 1.0f);
	_lightmanager.setPointLightLevel(2, 50);

	_lightmanager.addLight(new TestLight(vertices, 288, this), "p2");
	_lightmanager.setLightType(3, LightManager::type::point);
	_lightmanager.setPosition(3, -4.0f, 2.0f, -12.0f);
	_lightmanager.setAmbientColor(3, 0.05f, 0.05f, 0.05f);
	_lightmanager.setDiffuseColor(3, 0.8f, 0.8f, 0.8f);
	_lightmanager.setSpecularColor(3, 1.0f, 1.0f, 1.0f);
	_lightmanager.setPointLightLevel(3, 50);

	_lightmanager.addLight(new TestLight(vertices, 288, this), "p3");
	_lightmanager.setLightType(4, LightManager::type::point);
	_lightmanager.setPosition(4, 0.0f, 0.0f, -3.0f);
	_lightmanager.setAmbientColor(4, 0.05f, 0.05f, 0.05f);
	_lightmanager.setDiffuseColor(4, 0.8f, 0.8f, 0.8f);
	_lightmanager.setSpecularColor(4, 1.0f, 1.0f, 1.0f);
	_lightmanager.setPointLightLevel(4, 50);

	_lightmanager.addLight(new TestLight(vertices, 288), "s1");
	_lightmanager.setLightType(5, LightManager::type::cameraspot);
	_lightmanager.setAmbientColor(5, 0.0f, 0.0f, 0.0f);
	_lightmanager.setDiffuseColor(5, 1.0f, 1.0f, 1.0f);
	_lightmanager.setSpecularColor(5, 1.0f, 1.0f, 1.0f);
	_lightmanager.setPointLightLevel(5, 50);
	_lightmanager.setSpotLightCutOff(5, 10.5f, 17.0f);
}

void TestStage::_inputProcess() {
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
		if(e._keys[GLFW_MOUSE_BUTTON_LEFT])
			_camera->rotate(e._offsety, e._offsetx);
	}
	
}
void TestStage::loop() {
	//Step is divided into two parts: prepare and draw
	_inputProcess();
}

void TestStage::paint() {
}

//Object
TestObject::TestObject(float*vertices, int nvert, Stage* s):vertObject(s),Object(s){
	vertObject::setVertices(vertices, nvert);
	_drawer->gl_setShader("res/shaders/defaultObject.vert","res/shaders/defaultObject.frag");
	_material = new Material();
	_material->setShininess(0.1f);
	_texture.push_back(new Texture("res/textures/container2.png"));
	_texture.push_back(new Texture("res/textures/container2_specular.png"));
	init();
};

void TestObject::init() {
	//设置顶点格式
	int groups[] = { 3,3,2 };
	setVerticesFormatf(3, groups);
	_drawer->gl_setFormat(&_vertices[0], _nvert * sizeof(float), _format,
		&_indices[0], _nIndices * sizeof(unsigned int));
}

void TestObject::step() {
}

void TestObject::paint() {
	Shader* _shader = _drawer->gl_getShader();
	//Shader参数可调，应该对应Shader中所有Uniform变量
	_shader->setParameter(STAGE_NAME_VIEWPOS, _stage->getViewPoint());
	_shader->setParameter(STAGE_NAME_VIEWDIR, _stage->getViewDir());
	//_shader->setParameter("material.ambient", _material->getAmbient());
	_shader->setParameter(std::string(OBJECT_NAME_MATERIAL) + OBJECT_ATTR_DIFFTEX, 0);
	_shader->setParameter(std::string(OBJECT_NAME_MATERIAL) + OBJECT_ATTR_SPECTEX, 1);
	_shader->setParameter(std::string(OBJECT_NAME_MATERIAL) + OBJECT_ATTR_SHININESS, _material->getShininess());

	_shader->setParameter(STAGE_NAME_PROJECTION, _stage->getProjection());
	_shader->setParameter(STAGE_NAME_VIEW, _stage->getView());
	_shader->setParameter(OBJCET_NAME_MODEL, _model);

	_shader->setAmbientLight(_stage->manageLights().getAmbientLight());
	_shader->setPointLight(_stage->manageLights().getPointLight());
	_shader->setSpotLight(_stage->manageLights().getSpotLight());

	_texture[0]->use(GL_TEXTURE0);
	_texture[1]->use(GL_TEXTURE1);

	glDrawArrays(GL_TRIANGLES, 0, _nvert);
}


//Light
TestLight::TestLight(float *vertices, int nvert, Stage *s) :vertLight(s, vertices, nvert),Object(s){
	init();
}

void TestLight::init() {
	_drawer->gl_setShader("res/shaders/triangle.vert", "res/shaders/lightcube.frag");
	scale(0.2f, 0.2f, 0.2f);
	//设置顶点格式
	int groups[] = { 3,3,2 };
	setVerticesFormatf(3, groups);
	_drawer->gl_setFormat(&_vertices[0], _nvert * sizeof(float), _format,
		&_indices[0], _nIndices * sizeof(unsigned int));
}

void TestLight::step() {
	//_lightColor.x = sin((float)Time::GetTime() * 2.0f);
	//_lightColor.y = sin((float)Time::GetTime() * 0.7f);
	//_lightColor.z = sin((float)Time::GetTime() * 1.3f);
}

void TestLight::paint() {
	Shader* _shader = _drawer->gl_getShader();
	//stage = NULL, 则不参与绘图
	if (_stage) {
		_shader->setParameter("projection", _stage->getProjection());
		_shader->setParameter("view", _stage->getView());
		_shader->setParameter("model", _model);
		glDrawArrays(GL_TRIANGLES, 0, _nvert);
	}
}