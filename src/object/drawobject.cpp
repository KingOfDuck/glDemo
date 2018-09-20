#include "object.h"
#include "properties/shader.h"
#include "properties/material.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

drawObject::drawObject(float*vertices, int nvert, Stage *s):_rotate(0.0f,0.0f,0.0f),
	_position(0.0f,0.0f,0.0f),_scale(1.0f,1.0f,1.0f),_format(),
	_model(glm::mat4(1.0f)),_material(NULL),_shader(NULL),Object(s){
	if (!nvert) {
		_vertices = NULL;
		_nvert = 0;
	}
	else {
		_vertices = (float*)malloc(sizeof(float)*nvert);
		for (int i = 0; i < nvert; ++i) {
			_vertices[i] = vertices[i];
		}
		_nvert = nvert;
	}
	_ebo = -1;
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
}

drawObject::~drawObject() {
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
	if (_ebo >= 0) {
		glDeleteBuffers(1, &_ebo);
	}
	if (_material)
		delete _material;
	if (_vertices)
		free(_vertices);
	if (_shader)
		free(_shader);
}

void drawObject::draw() {
	glBindVertexArray(_vao);
	if (!_shader) {
		//TODO: Log Object do not have a shader?
		return;
	}
	_shader->use();
	this->paint();
	glBindVertexArray(0);
}

void drawObject::setVerticesFormatf(std::vector<int> oneLineFormat) {
	_format = oneLineFormat;
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*_nvert, _vertices, GL_STATIC_DRAW);

	int sum = 0;
	for (int i = 0; i < oneLineFormat.size(); ++i) {
		sum += oneLineFormat[i];
	}

	int total = 0;
	for (int i = 0; i < oneLineFormat.size(); ++i) {
		glVertexAttribPointer(i, oneLineFormat[i], GL_FLOAT, GL_FALSE, sum * sizeof(float), (void*)(total*sizeof(float)));
		total += oneLineFormat[i];
		glEnableVertexAttribArray(i);
	}
	glBindVertexArray(0);
}
void drawObject::setVerticesFormatf(int number, int* groups) {
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*_nvert, _vertices, GL_STATIC_DRAW);
	int sum = 0;
	for (int i = 0; i < number; ++i) {
		sum += groups[i];
	}
	int total = 0;
	for (int i = 0; i < number; ++i) {
		_format.push_back(groups[i]);
		glVertexAttribPointer(i, groups[i], GL_FLOAT, GL_FALSE, sum * sizeof(float), (void*)(total*sizeof(float)));
		glEnableVertexAttribArray(i);
		total += groups[i];
	}
	glBindVertexArray(0);
}

void drawObject::move(float x, float y, float z) {
	_position.x += x;
	_position.y += y;
	_position.z += z;
	_model = glm::translate(_model, _position);
}

void drawObject::moveTo(float x, float y, float z) {
	//回到原点
	_model = glm::translate(_model, -_position);
	_position.x = _position.y = _position.z = 0.0f;
	//再次移动
	move(x, y, z);
}

void drawObject::rotate(float z) {
	_rotate.z += z;
	_model = glm::rotate(_model, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void drawObject::rotateTo(float z) {
	_model = glm::rotate(_model, glm::radians(-_rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
	_rotate.z = 0;
	rotate(z);
}

void drawObject::scale(float x, float y, float z) {
	_scale.x *= x;
	_scale.y *= y;
	_scale.z *= z;
	_model = glm::scale(_model, glm::vec3(x, y, z));
}

void drawObject::scaleTo(float x, float y, float z) {
	_model = glm::scale(_model, glm::vec3(1/_scale.x, 1/_scale.y, 1/_scale.z));
	_scale.x = _scale.y = _scale.z = 1.0f;
	scale(x, y, z);
}

void drawObject::rotate(float degree, const glm::vec3&axis) {
	_rotate += axis;
	_model = glm::rotate(_model,glm::radians(degree),axis);
}