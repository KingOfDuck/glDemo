#include <glad/glad.h>

#include "TestObject.h"
#include "TestStage.h"
#include "../../AppWindow.h"
#include "../camera.h"
#include "../shader.h"
#include "../texture.h"

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

	_objects.push_back(reinterpret_cast<Object*>(new TestObject(vertices, 32)));
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
	_position.x = _position.y = _position.z = 0;
	init();
}
TestObject::TestObject(float*vertices, int nvert) :_vertices(vertices), _nvert(nvert) {
	_shader = new Shader("shaders/triangle.vert","shaders/triangle.frag");
	_texture.push_back(new Texture("textures/container.jpg",GL_RGB));
	_texture.push_back(new Texture("textures/awesomeface.png",GL_RGBA));
	_model = glm::vec3(0.0f, 0.0f, 0.0f);
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	setIndices(indices, 6);
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

void TestObject::draw() {
	glActiveTexture(GL_TEXTURE0);
	_texture[0]->use(); 
	glActiveTexture(GL_TEXTURE1);
	_texture[1]->use();
	_shader->use(); 
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void TestObject::setIndices(unsigned int* indices, int nind) {
	_indices = indices;
	_nind = nind;
}