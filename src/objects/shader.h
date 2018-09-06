#ifndef __SHADER_H
#define __SHADER_H

#define SHADER_VERT_COMPILE_ERROR -1
#define SHADER_FRAG_COMPILE_ERROR -2
#define SHADER_ERROR_FILENAME -3
class Shader {
private:
	unsigned int _id;//Program ID
	int _success;//success flag
	char *_info;//error information
	enum shadertype {
		vertex, fragment
	};
public:
	Shader(const char* vertex, const char* fragment);
	void use();
	void setInt(const char* name, int val);
	~Shader();
private:
	int compile(const char* filename, shadertype type);
	Shader();
};

#endif