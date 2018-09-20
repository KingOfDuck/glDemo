#include "ShaderManager.h"

#include <fstream>
#include <iostream>
#include <glad/glad.h>

std::map<std::string, int> ShaderManager::_idmap;
std::map<int, int> ShaderManager::_idused;

int ShaderManager::load(const char* vertex, const char* fragment) {
	//首先寻找map中是否存在
	std::string m = vertex;
	m += fragment;
	//如果存在则不编译
	auto tid = _idmap.find(m);
	if ( tid != _idmap.end()) {
		_idused[tid->second]++;
		return tid->second;
	}

	//通过文件名编译
	int vs, fs,success, id;
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
		if(info)
			free(info);
		return -1;
	}
	glDeleteShader(vs);
	glDeleteShader(fs);

	//将id添加到map中
	_idmap[m.c_str()] = id;
	_idused[id] = 1;

	return id;
}

void ShaderManager::load(int id) {
	if (_idused.find(id) != _idused.end()) {
		_idused[id]++;
	}
	else {
		//TODO: Log load id not exists
	}
}
void ShaderManager::remove(int id) {
	if (_idused.find(id) != _idused.end()) {
		_idused[id]--;
	}
	else {
		//TODO: Log remove id not exists
	}
}
int ShaderManager::compile(const char* filename, shadertype type) {
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