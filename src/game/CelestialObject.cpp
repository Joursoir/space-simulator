#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CelestialObject.hpp"
#include "../graphics/Texture.hpp"
#include "../graphics/Mesh.hpp"
#include "../objects.hpp"

using namespace glm;

Mesh *CelestialObject::sphere = 0;
Mesh *CelestialObject::circle = 0;

#define FULL_TURN 360.0f

void CelestialObject::InitializeMesh()
{
	sphere = form_sphere(36, 36);
	circle = form_circle(36);
}

void CelestialObject::SetPeriod(float a_orbital, float a_rotation)
{
	orbital_period = a_orbital;
	rotation_period = a_rotation;
	orbital_speed = (a_orbital == 0.0f) ? 0.0f : FULL_TURN / orbital_period;
	rotation_speed = (a_rotation == 0.0f) ? 0.0f : FULL_TURN / rotation_period;
}

void CelestialObject::SetRadius(float object_r, float orbital_r)
{
	object_radius = object_r;
	orbital_radius = orbital_r;
}

void CelestialObject::SetTilt(float angle)
{
	tilt_angle = radians(angle);
}

void CelestialObject::SetPosition(glm::vec3 orbital)
{
	orbital_pos = orbital;
}

void CelestialObject::Draw(float time, float game_speed,
	unsigned int model_loc)
{
	float
		orb_speed = orbital_speed * game_speed,
		rot_speed = rotation_speed * game_speed,
		moveX = sin(radians(time) * orb_speed) * orbital_radius,
		moveZ = cos(radians(time) * orb_speed) * orbital_radius;

	texture->Bind();

	mat4 sphere_model(1.0f);
	vec3 pos(orbital_pos.x - moveX, orbital_pos.y, orbital_pos.z - moveZ);
	sphere_model = translate(sphere_model, pos);
	sphere_model = rotate(sphere_model, tilt_angle, vec3(1.0f, 0.0f, 0.0f));
	sphere_model = rotate(sphere_model, radians(time) * rot_speed, vec3(0.0f, 0.0f, 1.0f));
	sphere_model = scale(sphere_model, vec3(object_radius, object_radius, object_radius));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, value_ptr(sphere_model));
	sphere->Draw();

	if(orbital_radius != 0.0f) {
		mat4 circle_model(1.0f);
		circle_model = translate(circle_model, orbital_pos);
		circle_model = scale(circle_model, vec3(orbital_radius, orbital_radius, orbital_radius));
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, value_ptr(circle_model));
		circle->Draw();
	}
}