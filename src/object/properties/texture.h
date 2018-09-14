#ifndef __TEXTURE_H
#define __TEXTURE_H

/*
	Texture class
*/
class Texture {
private:
	unsigned int _id;//纹理id
public:
	//使用文件名和颜色格式初始化纹理
	Texture(const char* filename, int format);

	//使用为X号纹理
	//ID应为GL_TEXTUREXX
	void use(int id);

	~Texture();
private:
	Texture();
};

#endif