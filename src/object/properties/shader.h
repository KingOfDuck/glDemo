#ifndef __SHADER_H
#define __SHADER_H
#include <glm/mat4x4.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <glad/glad.h>

#define SHADER_VERT_COMPILE_ERROR -1
#define SHADER_FRAG_COMPILE_ERROR -2
#define SHADER_ERROR_FILENAME -3

class Light;
class Texture;
class Shader {
private:
	unsigned int _id;//Program ID
public:
	static Shader* LoadFromFile(const char* vertex, const char* fragment);
	Shader* copy();

	void use();

	void setAmbientLight(Light* light);
	void setPointLight(const std::vector<Light*>& lights);
	void setSpotLight(const std::vector<Light*>& lights);



	template <typename T>
	void setParameter(const std::string& name, T val) {
		int l = glGetUniformLocation(_id, name.c_str());
		if (l < 0) {
			std::cout << name;
			return;
		}
		setParameter(l, val);
	}

	template <typename M>
	void setParameter(const char* name, M val) {
		int l = glGetUniformLocation(_id, name);
		if (l < 0) {
			std::cout << name;
			return;
		}
		setParameter(l, val);
	}

	~Shader();
private:
	void setParameter(int id, int val);
	void setParameter(int id, glm::vec3 color);
	void setParameter(int id, glm::mat4 matrix);
	void setParameter(int id, float val);
	void setParameter(int id, bool val);

	Shader();
	Shader(Shader &);
	Shader(Shader &&);
};

#endif