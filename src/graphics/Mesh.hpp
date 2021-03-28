#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <GL/glew.h>
#include "../graphics/Vertex.hpp"

class Mesh {
	GLuint VAO, VBO, EBO;
	size_t number_indices;

public:
	Mesh(Vertex *vertices, size_t num_vert,
		GLuint *indices, size_t num_indices);
	~Mesh();

	void Draw();
};

#endif /* ENGINE_VERTEX_H */
