#include "Mesh.h"
#include "properties/drawer.h"
#include <glad/glad.h>
#include <string>

Mesh::Mesh(std::vector<Vertex> *vertices, std::vector<unsigned int> *indices, 
	std::vector<Texture> *textures){
	this->_vertices = vertices;
	this->_indices = indices;
	this->_textures = textures;
	_drawer = Drawer::CreateDrawer(NULL);//Mesh不是Entity，不需要有obj
	_drawer->gl_setShader("res/shaders/defaultMesh.vert", "res/shaders/defaultMesh.frag");

	setupMesh();
}
/*
Mesh::Mesh() {
	_drawer = NULL;
}*/

Mesh::Mesh(Mesh& m) {
	_drawer = m._drawer;
	_vertices = m._vertices;
	_indices = m._indices;
	_textures = m._textures;
}

Mesh::Mesh(Mesh&& m) {
	_drawer = m._drawer;
	_vertices = m._vertices;
	_indices = m._indices;
	_textures = m._textures;
}


void Mesh::setupMesh() {
	std::vector<int> format;
	format.push_back(3);
	format.push_back(3);
	format.push_back(2);

	_drawer->gl_setFormat(&((*_vertices)[0]), _vertices->size() * sizeof(Vertex), format,
		&((*_indices)[0]), _indices->size() * sizeof(unsigned int));
}


void Mesh::paint() {
	_drawer->gl_drawMesh(this);
}