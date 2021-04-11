#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>

enum camera_move {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
	glm::vec3 position;
	glm::vec3 front, up, right;
	glm::vec3 world_up;

	GLfloat yaw; // around x
	GLfloat pitch; // around y

	GLfloat move_speed;
	GLfloat mouse_sensitivity;

	GLfloat fov;
	GLfloat near, far;
public:
	Camera(glm::vec3 a_pos = glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3 a_front = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 a_up = glm::vec3(0.0f, 1.0f, 0.0f),
		GLfloat a_yaw = -90.0f, GLfloat a_pitch = 0.0f);
	void SetSpeed(GLfloat a_speed) { move_speed = a_speed; }
	void SetSensitivity(GLfloat a_sens) { mouse_sensitivity = a_sens; }
	void SetPerspective(GLfloat a_fov, GLfloat a_near, GLfloat a_far)
		{ fov = a_fov; near = a_near; far = a_far; }

	glm::mat4 GetProjViewMatrix(int w_width, int w_height);
	glm::mat4 GetSkyboxMatrix(int w_width, int w_height);
	void Movement(camera_move direction, GLfloat deltaTime);
	void UpdateView(GLfloat delta_x, GLfloat delta_y);
	void UpdateFov(GLfloat delta_y);
private:
	void UpdateVectors();
};

#endif /* ENGINE_CAMERA_H */
