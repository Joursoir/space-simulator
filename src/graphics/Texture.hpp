#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

class Texture {
	int target;
	unsigned int texture_id;
public:
	Texture(int type);
	~Texture();

	int LoadImage(const char *path);
	int LoadImage(const char **paths);
	void Bind();
};

#endif /* ENGINE_TEXTURE_H */
