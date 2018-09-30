
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
* @brief 正式的网格，顶点格式固定，用于从模型文件中读取网格，为模型的属性
* @tip 若需要自由定点格式，使用vertObject
*/
class Mesh{
	friend class Model;
public:
	Drawer *_drawer;//绘图模块，与实体分离
	Model *_pModel;//记录所包含的model
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