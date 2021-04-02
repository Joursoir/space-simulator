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

const GLfloat
			init_yaw = -90.0f,
			init_pitch = 0.0f,
			init_speed = 2.5f,
			init_sensitivity = 0.25f,
			init_fov = glm::radians(45.0f);

class Camera {
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 world_up;

	GLfloat yaw; // around x
	GLfloat pitch; // around y

	GLfloat move_speed;
	GLfloat mouse_sensitivity;
	GLfloat fov;
public:
	Camera(glm::vec3 a_pos = glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3 a_front = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 a_up = glm::vec3(0.0f, 1.0f, 0.0f),
		GLfloat a_yaw = init_yaw, GLfloat a_pitch = init_pitch);

	glm::mat4 GetProjViewMatrix(int w_width, int w_height);
	glm::mat4 GetSkyboxMatrix(int w_width, int w_height);
	void Movement(camera_move direction, GLfloat deltaTime);
	void View(GLfloat delta_x, GLfloat delta_y);
	void Fov(GLfloat delta_y);
private:
	void UpdateVectors();
};

#endif /* ENGINE_CAMERA_H */
