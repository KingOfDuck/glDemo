#include <glad/glad.h>

#include "TestObject.h"
#include "TestStage.h"
#include "../../AppWindow.h"
#include "../camera.h"
#include "../shader.h"

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};

float texCoords[] = {
	0.0f,0.0f,
	1.0f,0.0f,
	0.5f,1.0f
};

void AppWindow::initStage() {
	_stage = new TestStage(this);
}

TestStage::TestStage(AppWindow *w) :
	Stage(w) {
	//TODO: Init Objects;
	_canvas = new Canvas(0.8f, 1.0f, 0.8f);
	_camera = new Camera();

	_objects.push_back(reinterpret_cast<Object*>(new TestObject(vertices, 9)));
}

void TestStage::step() {
	//Step is divided into two parts: prepare and draw
	//Preparing the informations for drawing: status, movements, textures, lightlings, shaders, ...
	for (auto i = _objects.begin(); i != _objects.end(); ++i) {
		//TODO: Objects Movement
	}

}

void TestStage::draw() {
	Stage::draw();//Canvas & Camera
	
	//Draw all objects
	for (auto i = _objects.begin(); i != _objects.end(); ++i) {
		(*i)->draw();
	}
}



TestObject::TestObject() :_vertices(NULL), _nvert(0) {
	init();
	_position.x = _position.y = _position.z = 0;
}
TestObject::TestObject(float*vertices, int nvert) :_vertices(vertices), _nvert(nvert) {
	_shader = new Shader("shaders/triangle.vert","shaders/triangle.frag");
	_model = glm::vec3(0.0f, 0.0f, 0.0f);
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	init();
};
TestObject::TestObject(float*vertices, int nvert, glm::vec3 &position) :
	_vertices(vertices), _nvert(nvert){
	_position = position;
	init();
}

void TestObject::bindBuffer() {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*_nvert, _vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void TestObject::draw() {
	_shader->use();
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}