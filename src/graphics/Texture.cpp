#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#include "Texture.hpp"

Texture::Texture(int type) : target(type)
{
	glGenTextures(1, &texture_id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture_id);
}

int Texture::LoadImage(const char *path)
{
	int width, height, nrChannels;
	unsigned char *image;

	glBindTexture(target, texture_id);

		image = stbi_load(path, &width, &height, &nrChannels, 0);
		if(!image)
			return 1;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image);
		stbi_image_free(image);

		glGenerateMipmap(target);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(target, 0);
	return 0;
}

int Texture::LoadImage(const char **paths)
{
	if(target != GL_TEXTURE_CUBE_MAP)
		return 1;

	int width, height, nrChannels;
	unsigned int i;
	unsigned char *image;

	glBindTexture(target, texture_id);

		for(i = 0; i < 6; i++) {
			image = stbi_load(paths[i], &width, &height, &nrChannels, 0);
			if(!image)
				return 1;

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			stbi_image_free(image);
		}

		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(target, 0);
	return 0;
}

void Texture::Bind()
{
	glBindTexture(target, texture_id);
}
