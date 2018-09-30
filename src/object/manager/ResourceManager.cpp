#include "ResourceManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../../lib/stb_image.h"
#include <fstream>
#include <iostream>
#include <glad/glad.h>

std::map<std::string, int> ResourceManager::_idmap_shader, ResourceManager::_idmap_texture;
std::map<int, int> ResourceManager::_idused_shader, ResourceManager::_idused_texture,
	ResourceManager::_idused_model;
std::map<std::string, Model*> ResourceManager::_map_model;
std::map<int, std::string> _map_modelindex, _map_textureIndex;//文件全局变量，对外不可见，记录modelindex和string对应

int ResourceManager::loadShader(const char* vertex, const char* fragment) {
	//首先寻找map中是否存在
	std::string m = vertex;
	m += fragment;
	
	//如果存在则不编译
	auto tid = _idmap_shader.find(m);
	if ( tid != _idmap_shader.end()) {
		_idused_shader[tid->second]++;
		return tid->second;
	}
	
	//如果不存在则注册Shader
	int id = registerShader(vertex, fragment);

	if (id >= 0) {
		//将id添加到map中
		_idmap_shader[m.c_str()] = id;
		_idused_shader[id] = 1;
	}
	return id;
}

int ResourceManager::loadTexture(const char* filename) {
	//首先寻找map中是否存在
	std::string m = filename;

	//如果存在则不load
	auto tid = _idmap_texture.find(m);
	if (tid != _idmap_texture.end()) {
		_idused_texture[tid->second]++;
		return tid->second;
	}

	//如果不存在则注册Texture
	int id = registerTexture(filename);

	if (id >= 0) {
		//将id添加到map中
		_map_textureIndex[id] = filename;
		_idmap_texture[m.c_str()] = id;
		_idused_texture[id] = 1;
	}
	return id;
}

Model ResourceManager::loadModel(const char* filename) {
	//首先寻找map中是否存在
	std::string m = filename;

	//如果存在则不load
	auto tid = _map_model.find(m);
	if (tid != _map_model.end()) {
		_idused_model[tid->second->_mid]++;
		return *(tid->second);
	}

	//如果不存在则注册Model
	Model* model = Model::loadFromFile(filename);
	model->_mid = registerNewModel(model);

	if (model) {
		//将id添加到map中
		_map_model[filename] = model;
		_map_modelindex[model->_mid] = filename;
		_idused_texture[model->_mid] = 1;

		return *model;
	}
	//TODO: LOG MODEL LOADING WRONG
	return Model();
}

void ResourceManager::useTexture(int id) {
	if (_idused_texture.find(id) != _idused_texture.end()) {
		_idused_texture[id]++;
	}
	else {
		//TODO: Log remove id not exists
	}
}

//分配mid
int ResourceManager::registerNewModel(Model *m) {
	for (int i = 0; i < _idused_model.size(); i++) {
		if (_idused_model[i] <= 0) {
			return i;
		}
	}
	return (int)(_idused_model.size() + 1);
}

int ResourceManager::registerShader(const char* vertex, const char* fragment) {
	//通过文件名编译
	int vs, fs, success, id;
	char* info = 0;
	std::string t;
	t = vertex;
	if (t.find(".vert") != std::string::npos) {
		vs = compile(vertex, shadertype::vertex);
	}
	else {
		//TODO:Log 文件名错误
		return -1;
	}

	if (vs == -1) {
		//TODO:Log 编译错误
		return -1;
	}

	t = fragment;
	if (t.find(".frag") != std::string::npos) {
		fs = compile(fragment, shadertype::fragment);
	}
	else {
		//TODO:Log 文件名错误
		return -1;
	}
	if (fs == -1) {
		//TODO:Log 编译错误
		return -1;
	}


	id = glCreateProgram();
	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		info = (char*)calloc(512, sizeof(char));
		glGetProgramInfoLog(id, 512, NULL, info);
		std::cout << info << std::endl;
		if (info)
			free(info);
		return -1;
	}
	glDeleteShader(vs);
	glDeleteShader(fs);
	
	return id;
}

void ResourceManager::removeShader(int id) {
	if (_idused_shader.find(id) != _idused_shader.end()) {
		_idused_shader[id]--;
	}
	else {
		//TODO: Log remove id not exists
	}
}
void ResourceManager::removeTexture(int id) {
	if (_idused_texture.find(id) != _idused_texture.end()) {
		if (--_idused_texture[id] <= 0) {
			_idmap_texture.erase(_map_textureIndex[id]);
			_map_textureIndex.erase(id);
			glDeleteTextures(1, (GLuint*)&id);
		}
	}
	else {
		//TODO: Log remove id not exists
	}
}

void ResourceManager::removeModel(int modelid) {
	if (_idused_model.find(modelid) != _idused_model.end()) {
		if (--_idused_model[modelid] <= 0) {
			delete _map_model[_map_modelindex[modelid]];
			_map_model.erase(_map_modelindex[modelid]);
			_map_modelindex.erase(modelid);
		}
	}
	else {
		//TODO: Log remove id not exists
	}
}

int ResourceManager::compile(const char* filename, shadertype type) {
	std::ifstream file(filename);
	char *program = 0;
	char *info;
	int success;
	int shader;
	if (type == vertex) {
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	//读取文件
	std::streampos pos = file.tellg();
	file.seekg(0, std::ios::end);
	pos = file.tellg();

	file.seekg(0);
	program = (char*)calloc(1 + pos, sizeof(char));
	file.read(program, pos);
	file.close();

	//编译Shader
	glShaderSource(shader, 1, (const GLchar* const*)&program, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		info = (char*)malloc(sizeof(char) * 512);
		glGetShaderInfoLog(shader, 512, NULL, info);
		std::cout << info;
		if(info)
			free(info);
		return -1;
	}

	//release malloc memories
	free(program);
	return shader;
}


int ResourceManager::registerTexture(const char* filename) {
	int w, h, channel, format;
	unsigned int id;

	unsigned char* data = stbi_load(filename, &w, &h, &channel, 0);
	if (!data) {
		std::cout << "Failed to load texture";
		return -1;
	}
	if (channel == 1)
		format = GL_RED;
	else if (channel == 3)
		format = GL_RGB;
	else if (channel == 4)
		format = GL_RGBA;
	else {
		//TODO: LOG unsupported texture format
		return -1;
	}
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	return id;
}