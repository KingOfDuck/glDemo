#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw/glfw3.h>

#include "TestObject.h"
#include "TestStage.h"
#include "../../AppWindow.h"
#include "../camera.h"
#include "../shader.h"
#include "../texture.h"
#include "../../utils/time.h"


float vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};
unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

void AppWindow::initStage() {
	_stage = new TestStage(this);
}

TestStage::TestStage(AppWindow *w) :
	Stage(w) {
	//TODO: Init Objects;
	_canvas = new Canvas(0.8f, 1.0f, 0.8f);
	_camera = new Camera();
	setPerspective(45.0f, (float)w->getClientWidth() / (float)w->getClientHeight(), 0.1f, 100.0f);
	
	_objects.push_back(reinterpret_cast<Object*>(new TestObject(vertices, 32, this)));
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
		_camera->rotate(e._offsety, e._offsetx);
	}
	
}
void TestStage::step() {
	//Step is divided into two parts: prepare and draw
	_inputProcess();

	//Preparing the informations for drawing: status, movements, textures, lightlings, shaders, ...
	for (auto i = _objects.begin(); i != _objects.end(); ++i) {
		//TODO: Objects Movement
		(*i)->step();
	}

}

void TestStage::draw() {
	Stage::draw();//Canvas & Camera
	
	//Draw all objects
	for (auto i = _objects.begin(); i != _objects.end(); ++i) {
		(*i)->draw();
	}
}

TestObject::TestObject(float*vertices, int nvert, Stage* s) :_vertices(vertices), _nvert(nvert),drawObject(s) {
	_shader = new Shader("shaders/triangle.vert","shaders/triangle.frag");
	_texture.push_back(new Texture("textures/container.jpg",GL_RGB));
	_texture.push_back(new Texture("textures/awesomeface.png",GL_RGBA));
	_stage = s;
	setIndices(indices, 6);
	init();
};

void TestObject::init() {
	bindBuffer();
	rotatex(-55.0f);
}
void TestObject::bindBuffer() {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*_nvert, _vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*_nind, _indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	_shader->use();
	_shader->setInt("tex", 0);
	_shader->setInt("tex2", 1);
}

void TestObject::step() {
	float t = (float)Time::DeltaTime();
	rotate(t*10);
}
void TestObject::draw() {
	glActiveTexture(GL_TEXTURE0);
	_texture[0]->use(); 
	glActiveTexture(GL_TEXTURE1);
	_texture[1]->use();
	_shader->use();
	_shader->setMatrix("projection", _stage->getProjection());
	_shader->setMatrix("view", _stage->getView());
	_shader->setMatrix("model", _model);
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void TestObject::setIndices(unsigned int* indices, int nind) {
	_indices = indices;
	_nind = nind;
}

void TestObject::rotatex(float angle) {
	_model = glm::rotate(_model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
}