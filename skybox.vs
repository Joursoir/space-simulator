#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 skip;

out vec3 tex_coords;

uniform mat4 proj_view;

void main()
{
	tex_coords = position;
	gl_Position = proj_view * vec4(position, 1.0);
}
