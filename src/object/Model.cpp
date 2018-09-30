#include "Model.h"
#include "manager/ResourceManager.h"
#include "properties/drawer.h"
#include <assimp/Importer.hpp>
#include <iostream>

Model::Model(const char* filename,Stage *s):Entity(s),Object(s){
	delete _drawer;
	_drawer = NULL;
	*this = ResourceManager::loadModel(filename);
	for (auto i : _meshes) {
		i->_pModel = this;
	}
}
//Private, Used for copy
Model::Model():Entity(NULL),Object(NULL) {
	delete _drawer;
	_drawer = NULL;
	_mid = -1;
	//TODO:Default Model
}
//拷贝构造重写，只拷贝指针地址
Model::Model(Model &m) :Object(m._stage), Entity(m._stage) {
	delete _drawer;
	_drawer = NULL;
	//Object
	_stage = m.Object::_stage;
	//_drawer = m.Entity::_drawer;
	//Entity位置数据拷贝时无任何作用，不拷贝
	//_model = m.Entity::_model;
	//_position = m.Entity::_position;
	//_rotate = m.Entity::_rotate;
	//_scale = m.Entity::_scale;
	//Model
	_meshes = m._meshes;
	for (auto i : _meshes) {
		i->_pModel = this;
	}
}

//拷贝构造重写，只拷贝指针地址
Model::Model(Model &&m):Object(m._stage), Entity(m._stage) {
	delete _drawer;
	_drawer = NULL;
	//Object
	_stage = m.Object::_stage;
	//_drawer = m.Entity::_drawer;
	//Entity位置数据拷贝时无任何作用，不拷贝
	//_model = m.Entity::_model;
	//_position = m.Entity::_position;
	//_rotate = m.Entity::_rotate;
	//_scale = m.Entity::_scale;
	//Model
	_meshes = m._meshes;
	for (auto i : _meshes) {
		i->_pModel = this;
	}
}

Model::~Model() {
	ResourceManager::removeModel(_mid);
}

Model& Model::operator = (const Model &m) {
	if (this == &m)
		return *this;
	this->_mid = m._mid;
	this->_meshes = m._meshes;
	//Entity位置数据拷贝时无任何作用，不拷贝
	//this->_model = m._model;
	//this->_position = m._position;
	//this->_rotate = m._rotate;
	//this->_scale = m._scale;
	return *this;
}

void Model::draw() {
	for (auto i = _meshes.begin(); i != _meshes.end(); i++) {
		(*i)->paint();//Mesh paint
	}
}

void Model::step() {

}

Model* Model::loadFromFile(const char* filename) {
	Model* res = new Model();
	std::vector<Mesh*> meshes = std::vector<Mesh*>();

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs
		| aiProcess_GenNormals);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		delete res;
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return NULL;
	}
	std::string path = std::string(filename);
	path = path.substr(0, path.find_last_of('/'));
	
	//递归写成循环，防止递归太多
	std::vector<aiNode*> stack;
	aiNode* tNode;

	stack.push_back(scene->mRootNode);

	while (!stack.empty()) {
		tNode = stack.back();
		stack.pop_back();
		
		processNode(tNode, scene, meshes, path);

		for (unsigned int i = 0; i < tNode->mNumChildren; i++) {
			stack.push_back(tNode->mChildren[i]);
		}
	}
	
	res->_meshes = meshes;
	return res;
}

void Model::processNode(aiNode* node, const aiScene* scene, std::vector<Mesh*> &meshes, std::string &path) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene, path));
	}
}

Mesh* Model::processMesh(aiMesh *mesh, const aiScene *scene, std::string &path) {
	std::vector<Vertex>* vertices = new std::vector<Vertex>();
	std::vector<unsigned int>* indices = new std::vector<unsigned int>;
	std::vector<Texture>* textures = new std::vector<Texture>();

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		// 处理顶点位置、法线和纹理坐标
		//顶点
		vertex.positon = glm::vec3(mesh->mVertices[i].x,
				mesh->mVertices[i].y, mesh->mVertices[i].z);
		//法线
		vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y,
			mesh->mNormals[i].z);
		//纹理
		if (mesh->mTextureCoords[0]){ // 网格是否有纹理坐标？
		
			vertex.texcoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
			vertex.texcoords = glm::vec2(0.0f, 0.0f);

		vertices->push_back(vertex);
	}
	// 处理索引
	for (unsigned int i = 0; i < mesh->mNumFaces; i++){
		aiFace &face = mesh->mFaces[i];//修改成引用
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices->push_back(face.mIndices[j]);
	}
	// 处理材质
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, Texture::type::diffuse, path);
		textures->insert(textures->end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material,
			aiTextureType_SPECULAR, Texture::type::specular, path);
		textures->insert(textures->end(), specularMaps.begin(), specularMaps.end());
	}

	return new Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type,
	Texture::type typeName, std::string& path) {
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++){
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture = Texture((path + '/' + str.C_Str()).c_str());
		texture.setType(typeName);
		textures.push_back(texture);
	}
	return textures;
}
