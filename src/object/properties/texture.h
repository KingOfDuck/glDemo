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
	unsigned int _id;//����id
	type _type;//��ͼ����
public:
	//ʹ���ļ�������ɫ��ʽ��ʼ������
	Texture(const char* filename);
	Texture(const Texture &);
	Texture(Texture &&);

	//ʹ��ΪX������
	//IDӦΪGL_TEXTUREXX
	void use(int id);

	Texture & operator = (const Texture &);
	inline type getType() { return _type; }
	inline void setType(type t) { _type = t; }

	~Texture();
private:
	Texture();
};

#endif