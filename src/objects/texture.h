#ifndef __TEXTURE_H
#define __TEXTURE_H

/*
	Texture class
*/
class Texture {
private:
	unsigned int _id;//����id
public:
	//ʹ���ļ�������ɫ��ʽ��ʼ������
	Texture(const char* filename, int format);

	//ʹ������
	void use();

	~Texture();
private:
	Texture();
};

#endif