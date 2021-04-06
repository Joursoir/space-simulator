#include <GL/glew.h>

#include "Mesh.hpp"

Mesh::Mesh(GLenum primitive, Vertex *vertices, size_t num_vert,
	GLuint *indices, size_t num_indices)
	: mode(primitive), number_indices(num_indices)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(Vertex),
			&vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(GLuint),
			&indices[0], GL_STATIC_DRAW);

		// attributes with coords
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(GLvoid *)0);
		glEnableVertexAttribArray(0);

		// attributes with texture
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(GLvoid *)offsetof(Vertex, tex_coords));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
		glDrawElements(mode, number_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
