#ifndef __SHADER_H
#define __SHADER_H
#include <glm/mat4x4.hpp>
#include <vector>
#include <string>

#define SHADER_VERT_COMPILE_ERROR -1
#define SHADER_FRAG_COMPILE_ERROR -2
#define SHADER_ERROR_FILENAME -3

class Light;
class Shader {
private:
	unsigned int _id;//Program ID
public:
	Shader(const char* vertex, const char* fragment);
	Shader* copy();
	void loadFromFile(const char* vertex, const char* fragment);

	void use();
	void setParameter(const char* name, int val);
	void setParameter(const char* name, const glm::vec3 &color);
	void setParameter(const char* name, const glm::mat4 &matrix);
	void setParameter(const char* name, float val);
	void setParameter(const char* name, bool val);
	void setAmbientLight(Light* light);
	void setPointLight(const std::vector<Light*>& lights);
	void setSpotLight(const std::vector<Light*>& lights);

	template <typename T>
	void setParameter(const std::string & str, T val);

	~Shader();
private:
	Shader();
	Shader(Shader &);
	Shader(Shader &&);
};

#endif