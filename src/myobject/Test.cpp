#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw/glfw3.h>

#include "TestObject.h"
#include "TestStage.h"
#include "TestLight.h"
#include "../AppWindow.h"
#include "../stage/camera.h"
#include "../object/properties/shader.h"
#include "../object/properties/texture.h"
#include "../utils/time.h"
#include "../object/properties/material.h"


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

void AppWindow::initStage() {
	_stage = new TestStage(this);
}

//Stage

TestStage::TestStage(AppWindow *w) :
	Stage(w) {
	//TODO: Init Objects;
	_canvas = new Canvas(0.0f, 0.0f, 0.0f);
	_camera = new Camera();
	setPerspective(45.0f, (float)w->getClientWidth() / (float)w->getClientHeight(), 0.1f, 100.0f);
	
	_lights.push_back(new TestLight(vertices, 288, this));
	for (int i = 0; i < 10; ++i) {
		TestObject* t = new TestObject(vertices, 288, this);
		t->moveTo(cubePositions[i].x,cubePositions[i].y,cubePositions[i].z);
		float angle = 20.0f * i;
		t->rotate(angle, glm::vec3(1.0f, 0.3f, 0.5f));
		_objects.push_back(t);
	}

	setAmbient(0, 0.1f);
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
void TestStage::step() {
	//Step is divided into two parts: prepare and draw
	_inputProcess();

	//Preparing the informations for drawing: status, movements, textures, lightlings, shaders, ...

	for (auto i = _lights.begin(); i != _lights.end(); ++i) {
		(*i)->step();
	}
	for (auto i = _objects.begin(); i != _objects.end(); ++i) {
		//TODO: Objects Movement
		(*i)->step();
	}

}

void TestStage::draw() {
	Stage::draw();//Canvas & Camera
	
	//Draw all objects and lights
	for (auto i = _lights.begin(); i != _lights.end(); ++i) {
		(*i)->draw();
	}
	for (auto i = _objects.begin(); i != _objects.end(); ++i) {
		(*i)->draw();
	}
}

//Object

TestObject::TestObject(float*vertices, int nvert, Stage* s):drawObject(s) {
	_vertices = vertices;
	_nvert = nvert;
	_shader = new Shader("res/shaders/triangle.vert","res/shaders/triangle.frag");
	_material = new Material();
	_texture.push_back(new Texture("res/textures/container2.png", GL_RGBA));
	_texture.push_back(new Texture("res/textures/container2_specular.png", GL_RGBA));
	_material->setShininess(0.1f);
	init();
};

void TestObject::init() {
	bindBuffer();
}
void TestObject::bindBuffer() {
	int groups[] = { 3,3,2 };
	setVerticesFormatf(3, groups);
}

void TestObject::step() {
}

void TestObject::paint() {
	_shader->use();
	_shader->setParameter("viewPos", _stage->getViewPoint());
	_shader->setParameter("material.ambient", _material->getAmbient());
	_shader->setParameter("material.diffuse", 0);
	_shader->setParameter("material.specular", 1);
	_shader->setParameter("material.shininess", _material->getShininess());

	if (_stage->getAmbientLight() != NULL) {
		_shader->setParameter("light.color", _stage->getAmbientLight()->getLightColor());
		_shader->setParameter("light.ambient", _stage->getAmbientLight()->getLightColor() * glm::vec3(0.2f));
		_shader->setParameter("light.diffuse", _stage->getAmbientLight()->getLightColor() * glm::vec3(0.5f));
		_shader->setParameter("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		_shader->setParameter("light.direction", glm::vec3(-0.2f,-1.0f,-0.3f));
	}

	_shader->setParameter("projection", _stage->getProjection());
	_shader->setParameter("view", _stage->getView());
	_shader->setParameter("model", _model);

	_texture[0]->use(GL_TEXTURE0);
	_texture[1]->use(GL_TEXTURE1);

	glDrawArrays(GL_TRIANGLES, 0, _nvert);
}

void TestObject::setIndices(unsigned int* indices, int nind) {
	_indices = indices;
	_nind = nind;
}

void TestObject::rotatex(float angle) {
	_model = glm::rotate(_model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
}

//Light
TestLight::TestLight(float *vertices, int nvert, Stage *s) :Light(vertices, nvert, s) {
	init();
}

void TestLight::init() {
	_shader = new Shader("res/shaders/triangle.vert", "res/shaders/lightcube.frag");
	_lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	moveTo(1.2f, 1.0f, 2.0f);
	scale(0.2f, 0.2f, 0.2f);
	int groups[] = { 3,3,2 };
	setVerticesFormatf(3, groups);
}

void TestLight::step() {
	//_lightColor.x = sin((float)Time::GetTime() * 2.0f);
	//_lightColor.y = sin((float)Time::GetTime() * 0.7f);
	//_lightColor.z = sin((float)Time::GetTime() * 1.3f);
}

void TestLight::paint() {
	_shader->use();
	_shader->setParameter("projection", _stage->getProjection());
	_shader->setParameter("view", _stage->getView());
	_shader->setParameter("model", _model);
	glDrawArrays(GL_TRIANGLES, 0, _nvert);
}