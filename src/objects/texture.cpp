#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../lib/stb_image.h"
#include <glad/glad.h>
#include <iostream>

Texture::Texture(const char* filename, int format) {
	int w, h, channel;
	unsigned char* data = stbi_load(filename, &w, &h, &channel, 0);
	if (!data) {
		std::cout << "Failed to load texture";
		return;
	}

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

void Texture::use() {
	glBindTexture(GL_TEXTURE_2D, _id);
}

Texture::~Texture() {
	glDeleteTextures(1, &_id);
}
