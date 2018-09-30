
/** @file: mesh.h
* @breif: Define the mesh data of the model.
* 
*/
#ifndef __MESH_H
#define __MESH_H

#include <glm/glm.hpp>
#include "properties/texture.h"
#include "properties/shader.h"
#include "object.h"
#include <vector>
struct Vertex {
	glm::vec3 positon;
	glm::vec3 normal;
	glm::vec2 texcoords;
};
class Model;
/** @class Mesh
* @brief ��ʽ�����񣬶����ʽ�̶������ڴ�ģ���ļ��ж�ȡ����Ϊģ�͵�����
* @tip ����Ҫ���ɶ����ʽ��ʹ��vertObject
*/
class Mesh{
	friend class Model;
public:
	Drawer *_drawer;//��ͼģ�飬��ʵ�����
	Model *_pModel;//��¼��������model
	std::vector<Vertex> *_vertices;
	std::vector<unsigned int> *_indices;
	std::vector<Texture> *_textures;
	Mesh(std::vector<Vertex> *_vertices, std::vector<unsigned int> *indices,
		std::vector<Texture> *textures);

	void paint();
private:
	Mesh();
	Mesh(Mesh&);
	Mesh(Mesh&&);
	void setupMesh();
};

#endif