#include "shader.h"
#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

//一个Shader必须同时有两个着色器，不使用默认着色器
Shader::Shader(const char* vertex, const char* fragment) {
	int vs, fs;

	std::string t;
	t = vertex;
	if (t.find(".vert") != std::string::npos) {
		vs = compile(vertex, shadertype::vertex);
	}
	else {
		_success = SHADER_ERROR_FILENAME;
		return;
	}

	if (vs == -1) {
		_success = SHADER_VERT_COMPILE_ERROR;
		return;
	}

	t = fragment;
	if (t.find(".frag")!= std::string::npos) {
		fs = compile(fragment, shadertype::fragment);
	}
	else {
		_success = SHADER_ERROR_FILENAME;
		return;
	}
	if (fs == -1) {
		_success = SHADER_FRAG_COMPILE_ERROR;
		return;
	}


	_id = glCreateProgram();
	glAttachShader(_id, vs);
	glAttachShader(_id, fs);
	glLinkProgram(_id);
	glGetProgramiv(_id, GL_LINK_STATUS, &_success);
	if (!_success) {
		_info = (char*)calloc(512, sizeof(char));
		glGetProgramInfoLog(_id, 512, NULL, _info);
		std::cout << _info << std::endl;
		return;
	}
	glDeleteShader(vs);
	glDeleteShader(fs);
}

void Shader::use() {
	glUseProgram(_id);
}
void Shader::setInt(const char* name, int val) {
	int l = glGetUniformLocation(_id, name);
	glUniform1i(l, val);
}
void Shader::setMatrix(const char* name, glm::mat4 &m) {
	int l = glGetUniformLocation(_id, name);
	glUniformMatrix4fv(l, 1, GL_FALSE, glm::value_ptr(m));
}
//使用int，出错用负数，未出错用正数
int Shader::compile(const char* filename, shadertype type) {
	std::ifstream file(filename);
	char *program = 0;
	int shader;
	_success = 0;
	_info = NULL;
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
	glGetShaderiv(shader, GL_COMPILE_STATUS, &_success);
	if (!_success) {
		_info = (char*)malloc(sizeof(char) * 512);
		glGetShaderInfoLog(shader, 512, NULL, _info);
		std::cout << _info;
		return -1;
	}

	//release malloc memories
	free(program);
	return shader;
}

Shader::~Shader() {
	glDeleteProgram(_id);
	if (_info)
		free(_info);
}