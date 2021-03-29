#include <glm/glm.hpp>

#include "objects.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/Vertex.hpp"

#define PI 3.1415926535

using namespace glm;

const int cube_num_v = 8;
Vertex cube_vertices[cube_num_v] = {
	// first 4 - up edge
	{ vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 0.0f) },
	{ vec3(0.5f, -0.5f, -0.5f), vec2(0.0f, 0.0f) },
	{ vec3(0.5f, 0.5f, -0.5f), vec2(0.0f, 0.0f) },
	{ vec3(-0.5f, 0.5f, -0.5f), vec2(0.0f, 0.0f) },
	{ vec3(0.5f, 0.5f, 0.5f), vec2(0.0f, 0.0f) },
	{ vec3(-0.5f, 0.5f, 0.5f), vec2(0.0f, 0.0f) },
	{ vec3(-0.5f, -0.5f, 0.5f), vec2(0.0f, 0.0f) },
	{ vec3(0.5f, -0.5f, 0.5f), vec2(0.0f, 0.0f) }
};

const int cube_num_i = 12 * 3;
GLuint cube_indices[cube_num_i] = {
	0, 1, 2, // up edge
 	0, 2, 3,
	2, 3, 4, // far edge
	3, 4, 5,
	0, 3, 5, // left edge
	0, 5, 6,
	0, 6, 7, // near edge
	0, 1, 7,
	1, 4, 7, // right edge
	1, 2, 4,
	4, 5, 7, // down edge
	4, 6, 7
};

Mesh *form_cube()
{
	return new Mesh(cube_vertices, cube_num_v, cube_indices, cube_num_i);
}

Mesh *form_sphere(int longitude_count, int latitude_count)
{
	/* The points on the sphere with radius r > 0 and center (x0, y0, z0)...
		...can be parameterized via:
	{
		x = x0 + R * sin(tetta) * cos(phi)
		y = y0 + R * sin(tetta) * sin(phi)
		z = z0 + R * cos(tetta)
		tetta : [0, PI];  phi : [0, 2PI]
	}
	or:
	{
		x = x0 + R * cos(phi) * cos(tetta)
		y = y0 + R * cos(phi) * sin(tetta)
		z = z0 + R * sin(phi)
	}
	our x0, y0, z0 = 0 */
	int i, j, idx, k1, k2;
	float x, y, z;
	float s, t;
	float radius = 1.0;

	// sectors
	float longitude_step = PI / longitude_count;
	float longitude_angle;

	// stacks
	float latitude_step = 2 * PI / latitude_count;
	float latitude_angle;

	int sphere_num_v = (longitude_count + 1) * (latitude_count + 1);
	Vertex *sphere_vertices = new Vertex[sphere_num_v];
	for(i = 0, idx = 0; i <= longitude_count; i++) {
		longitude_angle = i * longitude_step;
		z = radius * cos(longitude_angle);

		for(j = 0; j <= latitude_count; j++) {
			latitude_angle = j * latitude_step;

			x = radius * sinf(longitude_angle) * cosf(latitude_angle);
			y = radius * sinf(longitude_angle) * sinf(latitude_angle);
			sphere_vertices[idx].pos_coords = glm::vec3(x, y, z);

			s = (float)j / longitude_count;
			t = (float)i / latitude_count;
			sphere_vertices[idx].tex_coords = glm::vec2(s, t);
			idx++;
		}
	}

	int sphere_num_i = (longitude_count - 1) * latitude_count * 6;
	GLuint *sphere_indices = new GLuint[sphere_num_i];
	for(i = 0, idx = 0; i < longitude_count; i++) {
		k1 = i * (latitude_count+1);
		k2 = k1 + (latitude_count+1);

		for(j = 0; j < latitude_count; j++, k1++, k2++) {
			if(i != 0)
			{
				sphere_indices[idx++] = k1;
				sphere_indices[idx++] = k2;
				sphere_indices[idx++] = k1 + 1;
			}
			if(i != (longitude_count-1))
			{
				sphere_indices[idx++] = k1 + 1;
				sphere_indices[idx++] = k2;
				sphere_indices[idx++] = k2 + 1;
			}
		}
	}

	Mesh *sphere = new Mesh(sphere_vertices, sphere_num_v,
		sphere_indices, sphere_num_i);

	delete[] sphere_vertices;
	delete[] sphere_indices;
	return sphere;
}
