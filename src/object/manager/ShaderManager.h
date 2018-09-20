#ifndef __SHADERMANAGER_H
#define __SHADERMANAGER_H
#include <vector>
#include <map>
class ShaderManager {
	enum shadertype {
		vertex, fragment
	};
	static std::map<std::string, int> _idmap;
	static std::map<int, int> _idused;//记录id使用次数
public:
	static int load(const char* vertex, const char* fragment);
	static void load(int shaderid);
	static void remove(int shaderid);
private:
	static int compile(const char* filename, shadertype type);
};


#endif