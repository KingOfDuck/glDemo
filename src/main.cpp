/* @file main.cpp
* @brief Entrance of this program
	Also a place to save diaries
* @date 2018/09/27
*/
/*
	日志
	2018/09/27 TODO: Mesh共享vertices但不共享pModel，需要将Model中的vector*变为vector
					 Mesh中不再存储vector，而存储vector*，ResourceManager中储存的Model
					 vector<Mesh>储存实体vector,共享Mesh数组变为Mesh共享顶点数组
*/
#include "glDemo.h"

int main() {
	glDemoApp demo;
	demo.run();
	return 0;
}