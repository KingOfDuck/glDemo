#ifndef __TESTOBJECT_H
#define __TESTOBJECT_H

#include "../object/object.h"
#include <glm/vec3.hpp>
#include <vector>

class TestObject : drawObject {
private:
	unsigned int * _indices;
	int _nind;
	float _angle;
public:
	TestObject(float*vertices, int nvert, Stage* s);

	void setIndices(unsigned int* indices, int nind);
	void init();
	void bindBuffer();
	void rotatex(float angle);

	///override
	void draw();
	///override
	void step();
private:
	TestObject();
	TestObject(std::vector<float>* vertices);
	TestObject(std::vector<float>&vertices);
	TestObject(std::vector<float>* vertices, glm::vec3 &position);
	TestObject(std::vector<float>&vertices, glm::vec3 &position);
	TestObject(float*vertices, int nvert, glm::vec3 &position);
};
#endif