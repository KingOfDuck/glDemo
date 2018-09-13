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
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
	
	_lights.push_back(new TestLight(vertices, 216, this));
	_objects.push_back(reinterpret_cast<Object*>(new TestObject(vertices, 216, this)));

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
	_material->setAmbient(1.0f, 0.5f, 0.31f);
	_material->setDiffuse(1.0f, 0.5f, 0.31f);
	_material->setSpecular(0.5f, 0.5f, 0.5f);
	_material->setShininess(0.4f);
	init();
};

void TestObject::init() {
	bindBuffer();
	moveTo(1.3f, -0.5f, 0.4f);
}
void TestObject::bindBuffer() {
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*_nvert, _vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	_shader->use();
}

void TestObject::step() {
}

void TestObject::draw() {
	_shader->use();
	_shader->setParameter("viewPos", _stage->getViewPoint());
	_shader->setParameter("material.ambient", _material->getAmbient());
	_shader->setParameter("material.diffuse", _material->getDiffuse());
	_shader->setParameter("material.specular", _material->getSpecular());
	_shader->setParameter("material.shininess", _material->getShininess());

	if (_stage->getAmbientLight() != NULL) {
		_shader->setParameter("light.color", _stage->getAmbientLight()->getLightColor());
		_shader->setParameter("light.ambient", _stage->getAmbientLight()->getLightColor() * glm::vec3(0.2f));
		_shader->setParameter("light.diffuse", _stage->getAmbientLight()->getLightColor() * glm::vec3(0.5f));
		_shader->setParameter("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		_shader->setParameter("light.position", _stage->getAmbientLight()->getPosition());
	}

	_shader->setParameter("projection", _stage->getProjection());
	_shader->setParameter("view", _stage->getView());
	_shader->setParameter("model", _model);
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, _nvert);
	glBindVertexArray(0);
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
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 180, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void TestLight::step() {
	_lightColor.x = sin((float)Time::GetTime() * 2.0f);
	_lightColor.y = sin((float)Time::GetTime() * 0.7f);
	_lightColor.z = sin((float)Time::GetTime() * 1.3f);
}

void TestLight::draw() {
	_shader->use();
	_shader->setParameter("projection", _stage->getProjection());
	_shader->setParameter("view", _stage->getView());
	_shader->setParameter("model", _model);

	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, _nvert);
	glBindVertexArray(0);
}