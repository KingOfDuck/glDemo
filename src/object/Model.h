/** @file model.h
* @biref 模型
*/
#ifndef __MODEL_H
#define __MODEL_H
#include "Mesh.h"
#include "properties/texture.h"
#include <vector>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/** @class Model
* @biref 模型类
*/

class Model : public Entity{
	friend class ResourceManager;
	friend class Mesh;
	friend class GLDrawer;
private:
	int _mid;//Model id, 用于资源管理
	std::vector<Mesh*> _meshes;//设定为指针，避免拷贝Mesh顶点数据
public:
	//从文件读取模型
	Model(const char* filename, Stage* s);
	//拷贝模型
	Model& operator = (const Model &m);
	void draw();
	void step();
	void paint() {}
	virtual ~Model();
protected:
	static Model* loadFromFile(const char* filename);
	static void processNode(aiNode *node, const aiScene *scene, std::vector<Mesh*> &meshes, std::string& path);
	static Mesh* processMesh(aiMesh *mesh, const aiScene *scene, std::string& path);
	static std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		Texture::type Ttype, std::string& path);

private:
	Model();
	Model(Model &m);
	Model(Model &&m);
};
#endif