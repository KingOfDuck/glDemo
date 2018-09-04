#ifndef __TEXTURE_H
#define __TEXTURE_H

/*
	Texture class
*/
class Texture {
private:
	float * _vertices;
	int _nvert;
public:
	Texture(const char* filename);//使用文件名初始化纹理
private:
	Texture();
};

#endif