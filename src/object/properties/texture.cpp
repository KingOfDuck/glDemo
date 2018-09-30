#include "texture.h"
#include "../../../lib/stb_image.h"
#include <glad/glad.h>
#include <iostream>
#include "../manager/ResourceManager.h"

Texture::Texture(const char* filename) {
	_id = ResourceManager::loadTexture(filename);
	_type = type::unset;
}

Texture& Texture::operator = (const Texture &t) {
	if (this == &t) return *this;
	ResourceManager::useTexture(t._id);
	_id = t._id;
	_type = t._type;
	return *this;
}

Texture::Texture(const Texture& t) {
	ResourceManager::useTexture(t._id);
	_id = t._id;
	_type = t._type;
}
Texture::Texture(Texture&& t) {
	ResourceManager::useTexture(t._id);
	_id = t._id;
	_type = t._type;
}

void Texture::use(int glid) {
	glActiveTexture(glid);
	glBindTexture(GL_TEXTURE_2D, _id);
}

Texture::~Texture() {
	ResourceManager::removeTexture(_id);
}
