/** @filename object.h
* @brief Base objects
* @update 2018/09/25 Move all base objects to object.h
*/
#ifndef __OBJECT_H
#define __OBJECT_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

#define OBJCET_NAME_MODEL			"model"				//模型矩阵
#define OBJECT_NAME_MATERIAL		"material"
#define OBJECT_ATTR_DIFFCOLOR		".diffuse_color"
#define OBJECT_ATTR_SPECCOLOR		".specular_color"	
#define OBJECT_ATTR_USETEXTURE		".useTexture"		//Use Texutre
#define OBJECT_ATTR_DIFFTEX			".diffuse"			//Deffuse Texture
#define OBJECT_ATTR_SPECTEX			".specular"			//Specular Texture
#define OBJECT_ATTR_SHININESS		".shininess"
#define OBJECT_ATTR_NUMDIFFTEX		".nDiffuse"
#define OBJECT_ATTR_NUMSPECTEX		".nSpecular"

class Shader;
class Texture;
class Stage;
class Material;
class Drawer;
/** @class Object
* @brief Base class for all objects. An object must be belonged to a stage.
*/
class Object {
	friend class Stage;
protected:
	Stage *_stage;//每一个Object都必须包含于stage中，记录其Stage
public:
	Object(Stage *s) :_stage(s) { _stage = s; }
	virtual void step() = 0;
	virtual ~Object(){}
protected:
	virtual void draw() = 0;//接口，每一个Object必须draw
private:
	Object();
};

//Canvas, background
class Canvas: public Object{
	friend class Stage;
private:
	float _red, _green, _blue, _alpha;
public:
	Canvas();
	Canvas(float red, float green, float blue, float alpha = 1.0f);
	Canvas(glm::vec3 bgColor, float alpha = 1.0f);
	Canvas(glm::vec4 bgColor);


	//Canvas不存在step
	inline void step() {};
protected:
	void draw();

	~Canvas();
};


/** @class Entity
* @brief Entity Object, 实体物体，包含物体基本位置信息，提供三维变换接口
* @inderface void step()
* @banned Entity()
*/
class Entity : virtual public Object {
protected:
	//Geometric
	glm::vec3 _position;//位置，初始在原点
	glm::vec3 _scale;//缩放，初始为1
	glm::vec3 _rotate;//物体朝向，初始为0
	glm::mat4 _model;//模型视图矩阵，初始化为单位矩阵
	Drawer *_drawer;//绘图模块，与实体分离
public:
	Entity(Stage* s);
	virtual ~Entity();

	virtual void paint() = 0;
	virtual void step() = 0;
	inline const glm::vec3& getPosition() { return _position; }
	inline const glm::mat4& getModelMatrix() { return _model; }

	//移动
	void move(float x, float y, float z);
	//移动至
	void moveTo(float x, float y, float z);
	//只允许旋转z轴
	void rotate(float zdegree);
	//只允许旋转z轴
	void rotateTo(float zdegree);
	//开放旋转
	void rotate(float degree, const glm::vec3&axis);
	//缩放
	void scale(float x, float y, float z);
	//缩放至
	void scaleTo(float x, float y, float z);

protected:
	//一般不能继承。实体draw通过drawer实现
	virtual void draw();


private:
	Entity();
};



/** @class vertObejct(interface)
* @brief 自由顶点物体，继承至Entity，可自由设置顶点格式，贴图或材质，用于拥有自定义数据的物体
	自由顶点物体的着色器需要自行配置，因此，通常来说，自由顶点物体的paint步骤如下：
	1、是否需要覆盖默认着色器，如果是，则需手动编写顶点/片段着色器并使用setShader()覆盖
	2、在重写的paint()方法中，通过_drawer->gl_getShader()获得着色器
	3、使用shader->setParameter()方法来设置所需要传递的uniform参数
	4、使用glDrawArray()/glDrawElement()来绘制自由顶点物体
	通常来说，shader需要配置的参数有：
		灯光setAmbient/Point/SpotLight()
		材质material.diffuse/specular
		视点viewPos
		视向viewDir
		视图矩阵 model/view/projection
	同时，拥有贴图的物体还需要激活贴图
		texture[0]->use()
* @interface void step()
* @interface void draw()
*/
class vertObject : public Entity{
protected:
	float * _vertices;//顶点数据
	unsigned int _nvert;//顶点个数
	unsigned int * _indices;//索引数据
	unsigned int _nIndices;//索引个数
	std::vector<int> _format;//顶点排列格式
	Material* _material;//材质，可选（光照无材质）
	std::vector<Texture*> _texture;//纹理，可选
public:
	vertObject(Stage *s);
	virtual ~vertObject();

	virtual void step() = 0;
	virtual void paint() = 0;
protected:
	//设置顶点格式
	//@oneLineFormat 每一行格式说明，例如：2 2 3表示一行有2+2+3=7个数据
	//	且分为2，2，3三组
	void setupFormat();
	void setVerticesFormatf(int number, int* groups);
	//设置索引
	void setIndices(unsigned int* indices, unsigned int _nindices);
	//设置顶点
	void setVertices(float*vertices, int nvert);
};
#endif