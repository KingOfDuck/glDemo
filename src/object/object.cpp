#include "object.h"
#include "properties/shader.h"
#include "properties/material.h"
#include "properties/drawer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Entity::Entity(Stage *s):_rotate(0.0f,0.0f,0.0f), _model(glm::mat4(1.0f)),
	_position(0.0f,0.0f,0.0f),_scale(1.0f,1.0f,1.0f),Object(s){
	_drawer = Drawer::CreateDrawer(this);
}

void Entity::draw() {
	if(_drawer)
		_drawer->draw();
}

void Entity::move(float x, float y, float z) {
	_position.x += x;
	_position.y += y;
	_position.z += z;
	_model = glm::translate(_model, glm::vec3(_position.x / _scale.x,
		_position.y / _scale.y, _position.z / _scale.z));
}

void Entity::moveTo(float x, float y, float z) {
	//回到原点
	_model = glm::translate(_model, -_position);
	_position.x = _position.y = _position.z = 0.0f;
	//再次移动
	move(x, y, z);
}

void Entity::rotate(float z) {
	_rotate.z += z;
	_model = glm::rotate(_model, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Entity::rotateTo(float z) {
	_model = glm::rotate(_model, glm::radians(-_rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
	_rotate.z = 0;
	rotate(z);
}

void Entity::scale(float x, float y, float z) {
	if (!x || !y || !z) {
		//TODO: Log wrong scale!
		return;
	}
	_scale.x *= x;
	_scale.y *= y;
	_scale.z *= z;
	_model = glm::scale(_model, glm::vec3(x, y, z));
}

void Entity::scaleTo(float x, float y, float z) {
	if (!x || !y || !z) {
		//TODO: Log wrong scale!
		return;
	}
	_model = glm::scale(_model, glm::vec3(1/_scale.x, 1/_scale.y, 1/_scale.z));
	_scale.x = _scale.y = _scale.z = 1.0f;
	scale(x, y, z);
}

void Entity::rotate(float degree, const glm::vec3&axis) {
	_rotate += axis;
	_model = glm::rotate(_model,glm::radians(degree),axis);
}

Entity::~Entity() {
	if (_drawer)
		delete _drawer;
}

vertObject::vertObject(Stage *s) :Object(s), Entity(s),
_format(), _material(NULL), _indices(NULL), _nIndices(0),
_nvert(0), _vertices(NULL) {
}

vertObject::~vertObject() {
	if (_material)
		delete _material;
	if (_vertices)
		free(_vertices);
}

void vertObject::setupFormat() {
	//TODO: WARN no vertices
	_drawer->gl_setFormat(_vertices, _nvert * sizeof(float), _format,
		_indices,_nIndices*sizeof(int));
}

void vertObject::setVerticesFormatf(int number, int* groups) {
	_format.clear();
	for (int i = 0; i < number; ++i) {
		_format.push_back(groups[i]);
	}
}

void vertObject::setIndices(unsigned int * indices, unsigned int nindices) {
	if (indices) {
		_indices = (unsigned int*)malloc(sizeof(unsigned int)*nindices);
		for (unsigned int i = 0; i < nindices; ++i) {
			_indices[i] = indices[i];
		}
		_nIndices = nindices;
	}
}

void vertObject::setVertices(float*vertices, int nvert) {
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
}