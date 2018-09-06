#ifndef __TESTOBJECT_H
#define __TESTOBJECT_H

#include "../object.h"
#include <glm/vec3.hpp>
#include <vector>

class TestObject : drawObject {
private:
	float * _vertices;
	int _nvert;
	unsigned int * _indices;
	int _nind;
public:
	TestObject();
	TestObject(float*vertices, int nvert);
	TestObject(float*vertices, int nvert, glm::vec3 &position);

	void move(float x, float y, float z) {
		_position.x += x;
		_position.y += y;
		_position.z += z;
	}
	void moveTo(float x, float y, float z) {
		_position.x = x;
		_position.y = y;
		_position.z = z;
	}
	void setIndices(unsigned int* indices, int nind);
	inline void init() {
		bindBuffer();
	}
	void bindBuffer();
	void draw();
private:
	TestObject(std::vector<float>* vertices);
	TestObject(std::vector<float>&vertices);
	TestObject(std::vector<float>* vertices, glm::vec3 &position);
	TestObject(std::vector<float>&vertices, glm::vec3 &position);
};
#endif