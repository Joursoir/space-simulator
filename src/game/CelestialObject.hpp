#ifndef ENGINE_CELESTIAL_OBJECT_H
#define ENGINE_CELESTIAL_OBJECT_H

#include <glm/glm.hpp>

#include "../xstdlib/xstdlib.hpp"

class Texture;
class Mesh;

class CelestialObject {
	Texture *texture;

	static Mesh *sphere;
	static Mesh *circle;

	struct linked_list<CelestialObject> *slaves;

	/* time a given astronomical object takes to complete
	one orbit around another object */
	float orbital_period;
	float orbital_speed;
	float orbital_radius;
	glm::vec3 orbital_pos;

	/* time that the objects takes to complete a single revolution
	around its axis of rotation relative to the background stars */
	float rotation_period;
	float rotation_speed;
	float rotation_axis_tilt;
	float rotation_ecliptic_tilt;

	float object_radius;
public:
	CelestialObject(Texture *t) : texture(t), slaves(0) { }
	static void InitializeMesh();
	void SetPeriod(float a_orbital, float a_rotation);
	void SetRadius(float object_r, float orbital_r);
	void SetTilts(float rot_axis, float rot_ecliptic);
	void SetPosition(glm::vec3 orbital);

	void AddSlave(CelestialObject *slave);
	void Draw(float time, float game_speed, unsigned int model_loc);

};

#endif /* ENGINE_CELESTIAL_OBJECT_H */
