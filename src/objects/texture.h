#ifndef __TEXTURE_H
#define __TEXTURE_H

/*
	Texture class
*/
class Texture {
private:
	unsigned int _id;//����id
public:
	Texture(const char* filename, int format);//ʹ���ļ�������ɫ��ʽ��ʼ������
	void use();
	~Texture();
private:
	Texture();
};

#endif