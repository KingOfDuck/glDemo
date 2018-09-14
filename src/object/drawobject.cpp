#include "object.h"
#include "properties/shader.h"
#include "properties/material.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

drawObject::drawObject(Stage *s):_direction(0.0f),_position(glm::vec3(0.0f,0.0f,0.0f)),
	_model(glm::mat4(1.0f)),_material(NULL),Object(s){
	_vertices = NULL;
	_nvert = 0;
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
}

void drawObject::draw() {
	glBindVertexArray(_vao);
	this->paint();
	glBindVertexArray(0);
}

void drawObject::setVerticesFormatf(std::vector<int> oneLineFormat) {
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
	_model = glm::translate(glm::mat4(1.0f), _position);
}

void drawObject::moveTo(float x, float y, float z) {
	_position.x = x;
	_position.y = y;
	_position.z = z;

	_model = glm::translate(glm::mat4(1.0f), _position);
}

void drawObject::rotate(float z) {
	_model = glm::rotate(_model, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void drawObject::rotateTo(float z) {
	_model = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void drawObject::scale(float x, float y, float z) {
	_model = glm::scale(_model, glm::vec3(x, y, z));
}

void drawObject::scaleTo(float x, float y, float z) {
	_model = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void drawObject::rotate(float degree, const glm::vec3&axis) {
	_model = glm::rotate(_model,glm::radians(degree),axis);
}