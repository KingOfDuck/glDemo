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
	glm::vec3 ambient;//����������ɫ
	glm::vec3 diffuse;//��������ɫ
	glm::vec3 specular;//���淴����ɫ
	float shininess = 32.0f;//���������ȣ�һ��Ϊ2/4/8/16/32/64��Ĭ��Ϊ32
public:

	Material() :ambient(glm::vec3(1.0f)), diffuse(glm::vec3(1.0f)), specular(glm::vec3(1.0f)){}

	//Choose a kind of Material in the default materials.
	void setMaterial(materials m);

	//���û���������ɫ
	inline void setAmbient(float red, float green, float blue) { ambient.r = red, ambient.g = green, ambient.b = blue; };
	inline void setAmbient(const glm::vec3& a) { ambient = a; }
	//������������ɫ
	inline void setDiffuse(float red, float green, float blue){ diffuse.r = red, diffuse.g = green, diffuse.b = blue; }
	inline void setDiffuse(const glm::vec3 &d) { diffuse = d; }
	//���þ��淴����ɫ
	inline void setSpecular(float red, float green, float blue) { specular.r = red, specular.g = green, specular.b = blue; }
	inline void setSpecular(const glm::vec3 &d) { specular = d; }
	//���÷���ǿ�ȣ���ΧΪ0.0f-1.0f
	inline void setShininess(float s) { shininess = s * 128.0f;/*Ĭ��1.0f�����Ϊ128.0*/ }

	inline const glm::vec3& getAmbient() { return ambient; }
	inline const glm::vec3& getDiffuse() { return diffuse; }
	inline const glm::vec3& getSpecular() { return specular; }
	inline float getShininess() { return shininess; }
private:
	//����������ݣ��������ݴ�External data��ȡ��
	//@caller public:setMaterial()
	void assginMaterialData(const std::vector<float> &data);
};
#endif