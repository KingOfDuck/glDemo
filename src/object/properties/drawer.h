/** @filename drawer.h
* @brief Graphics tools
* @created 2018/09/25
*/
#ifndef __GRAPHOBJECT_H
#define __GRAPHOBJECT_H
#include <vector>
#include <glad/glad.h>
#include "texture.h"


/** @class Drawer
* @brief An object must have a drawer if it wants to show in the stage
*/
class Entity;
class Shader;
class Mesh;
class Drawer{
protected:
	Entity * _obj;//��¼���иû�ͼģ���ָ��
public:
	Drawer(Entity * obj);
	static Drawer* CreateDrawer(Entity * obj);

	//draw�������ڲ����ã��û�ֻ����дpaint����
	virtual void draw() = 0;

	//GL
	virtual void gl_setFormat(void* vertices, GLsizeiptr vsize, std::vector<int> oneLineFormat, 
		unsigned int* indices = NULL, GLsizeiptr isize = 0) = 0;
	virtual void gl_setShader(const char* vertshader, const char* fragshader) = 0;
	virtual void gl_drawMesh(Mesh* _mesh) = 0;
	virtual Shader* gl_getShader() = 0;

	virtual ~Drawer() {}
private:
	Drawer();
};

/** @class GLDrawer
* @brief graphics for OpenGL
*/
class GLDrawer : public Drawer {
protected:
	//Data
	unsigned int _vbo;//���㻺�����
	unsigned int _vao;//�����������
	unsigned int _ebo;//������������ѡ����Ҫ�ֶ�����id

	//Properties
	Shader* _shader;//��ɫ��������
public:
	GLDrawer(Entity* obj);

	void draw();

	virtual void gl_setShader(const char* vertshader, const char* fragshader);
	virtual void gl_setFormat(void* vertices, GLsizeiptr vsize, std::vector<int> oneLineFormat,
		unsigned int* indices = NULL, GLsizeiptr isize = 0);
	virtual void gl_drawMesh(Mesh* _mesh);
	inline Shader* gl_getShader() { return _shader; };
	virtual ~GLDrawer();
private:
	GLDrawer();
};

#endif