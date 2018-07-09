#include "object.h"

#include <glad/glad.h>
Canvas::Canvas():
	_red(1.0f),_green(1.0f),_blue(1.0f),_alpha(1.0f){

}
Canvas::Canvas(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) :
	_red(red),_green(green),_blue(blue),_alpha(alpha) {

}
Canvas::Canvas(glm::vec3 color, GLfloat alpha):
	_alpha(alpha){
	_red = color.x;
	_green = color.y;
	_blue = color.z;
}
Canvas::Canvas(glm::vec4 color) {
	_red = color.x;
	_green = color.y;
	_blue = color.z;
	_alpha = color.w;
}

//Before drawing on a Canvas, clear the screen first
void Canvas::draw() {
	glClearColor(_red, _green, _blue, _alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

Canvas::~Canvas(){

}