#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 tex_pos;

out vec2 tex_coords;

uniform mat4 model;
uniform mat4 proj_view;

void main()
{
	gl_Position = proj_view * model * vec4(position, 1.0f);
	tex_coords = vec2(tex_pos.x, 1.0f - tex_pos.y);
}
