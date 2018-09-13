#ifndef __MATERIAL_H
#define __MATERIAL_H
#include<glm/vec3.hpp>
#include <vector>

class Material{

	//Matreirals data comes from http://devernay.free.fr/cours/opengl/materials.html
	enum materials {
		emerald,
		jade,
		obsidian,
		pearl,
		ruby,
		turquoise,
		brass,
		bronze,
		chrome,
		copper,
		gold,
		silver,
		black_plastic,
		cyan_plastic,
		green_plastic,
		red_plastic,
		white_plastic,
		yellow_plastic,
		black_rubber,
		cyan_rubber,
		green_rubber,
		red_rubber,
		white_rubber,
		yellow_rubber,
	};
private:
	glm::vec3 ambient;//环境反射颜色
	glm::vec3 diffuse;//漫反射颜色
	glm::vec3 specular;//镜面反射颜色
	float shininess = 32.0f;//镜面明亮度，一般为2/4/8/16/32/64，默认为32
public:

	Material() :ambient(glm::vec3(1.0f)), diffuse(glm::vec3(1.0f)), specular(glm::vec3(1.0f)){}

	//Choose a kind of Material in the default materials.
	void setMaterial(materials m);

	//设置环境反射颜色
	inline void setAmbient(float red, float green, float blue) { ambient.r = red, ambient.g = green, ambient.b = blue; };
	inline void setAmbient(const glm::vec3& a) { ambient = a; }
	//设置漫反射颜色
	inline void setDiffuse(float red, float green, float blue){ diffuse.r = red, diffuse.g = green, diffuse.b = blue; }
	inline void setDiffuse(const glm::vec3 &d) { diffuse = d; }
	//设置镜面反射颜色
	inline void setSpecular(float red, float green, float blue) { specular.r = red, specular.g = green, specular.b = blue; }
	inline void setSpecular(const glm::vec3 &d) { specular = d; }
	//设置反光强度，范围为0.0f-1.0f
	inline void setShininess(float s) { shininess = s * 128.0f;/*默认1.0f反光度为128.0*/ }

	inline const glm::vec3& getAmbient() { return ambient; }
	inline const glm::vec3& getDiffuse() { return diffuse; }
	inline const glm::vec3& getSpecular() { return specular; }
	inline float getShininess() { return shininess; }
private:
	//分配材质数据，材质数据从External data中取得
	//@caller public:setMaterial()
	void assginMaterialData(const std::vector<float> &data);
};
#endif