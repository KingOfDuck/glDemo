#ifndef __TEXTURE_H
#define __TEXTURE_H

/*
	Texture class
*/
class Texture {
public:
	enum type {
		unset,
		diffuse,
		specular
	};
private:
	unsigned int _id;//纹理id
	type _type;//贴图类型
public:
	//使用文件名和颜色格式初始化纹理
	Texture(const char* filename);
	Texture(const Texture &);
	Texture(Texture &&);

	//使用为X号纹理
	//ID应为GL_TEXTUREXX
	void use(int id);

	Texture & operator = (const Texture &);
	inline type getType() { return _type; }
	inline void setType(type t) { _type = t; }

	~Texture();
private:
	Texture();
};

#endif