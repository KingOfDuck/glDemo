#include "object.h"
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

drawObject::drawObject(Stage *s):_direction(0.0f),_position(glm::vec3(0.0f,0.0f,0.0f)),
	_model(glm::mat4(1.0f)),Object(s){
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

void drawObject::setTrans(const char* name) {
	_shader->setMatrix(name, _model);
}