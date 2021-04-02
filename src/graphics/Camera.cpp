#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"
using namespace glm;

Camera::Camera(vec3 a_pos, vec3 a_front, vec3 a_up,
	GLfloat a_yaw, GLfloat a_pitch)
	: move_speed(init_speed),
	mouse_sensitivity(init_sensitivity),
	fov(init_fov)
{
	position = a_pos;
	up = a_up;
	world_up = up;
	yaw = a_yaw;
	pitch = a_pitch;
	UpdateVectors();
}

mat4 Camera::GetProjViewMatrix(int w_width, int w_height)
{
	return 
		perspective(fov, (GLfloat)w_width / (GLfloat)w_height, 0.1f, 100.0f) *
		lookAt(position, position + front, up);
}

mat4 Camera::GetSkyboxMatrix(int w_width, int w_height)
{
	return 
		perspective(fov, (GLfloat)w_width / (GLfloat)w_height, 0.1f, 100.0f) *
		mat4(mat3(lookAt(position, position + front, up)));
}

void Camera::Movement(camera_move direction, GLfloat delta_time)
{
	GLfloat velocity;
	velocity = move_speed * delta_time;
	switch(direction) {
	case FORWARD:
		position += front * velocity;
		break;
	case BACKWARD:
		position -= front * velocity;
		break;
	case LEFT:
		position -= right * velocity;
		break;
	case RIGHT:
		position += right * velocity;
		break;
	}
	UpdateVectors();
}

void Camera::View(GLfloat delta_x, GLfloat delta_y)
{
	yaw += delta_x * mouse_sensitivity;
	pitch -= delta_y * mouse_sensitivity; // if '+' then inverse

	if(pitch > 89.0f)
		pitch = 89.0f;
	else if(pitch < -89.0f)
		pitch = -89.0f;

	UpdateVectors();
}

void Camera::Fov(GLfloat delta_y)
{
	if(!delta_y)
		return;

	fov -= radians(delta_y);
	if(fov > radians(45.0f))
		fov = radians(45.0f);
	else if(fov < radians(1.0f))
		fov = radians(1.0f);
}

void Camera::UpdateVectors()
{
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));

	/* Normalize the vectors, because their length gets closer to 0 
	the more you look up or down which results in slower movement. */
	right = normalize(cross(front, world_up));
	up = normalize(cross(right, front));
}
