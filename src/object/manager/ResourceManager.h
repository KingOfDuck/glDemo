#ifndef __SHADERMANAGER_H
#define __SHADERMANAGER_H
#include <vector>
#include <map>
#include "../Model.h"
class ResourceManager {
	enum shadertype {
		vertex, fragment
	};
	static std::map<std::string, int> _idmap_shader, _idmap_texture;
	static std::map<std::string, Model*> _map_model;
	static std::map<int, int> _idused_shader, _idused_texture, _idused_model;//记录id使用次数
public:
	static int loadShader(const char* vertex, const char* fragment);
	static void removeShader(int shaderid);
	
	static int loadTexture(const char* filename);
	static void useTexture(int id);
	static void removeTexture(int textureid);

	static Model loadModel(const char* filename);
	static void removeModel(int modelid);
private:
	static int registerShader(const char* vertex, const char* fragment);
	static int compile(const char* filename, shadertype type);
	static int registerTexture(const char* filename);
	static int registerNewModel(Model *m);
};


#endif