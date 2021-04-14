#include <stdio.h>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../application/Application.hpp"
#include "../window/Window.hpp"
#include "../window/EventsManager.hpp"
#include "../window/Events.hpp"
#include "../graphics/Camera.hpp"
#include "../graphics/Mesh.hpp"
#include "../graphics/Shader.hpp"
#include "../graphics/Texture.hpp"
#include "CelestialObject.hpp"
#include "objects.hpp"

using namespace glm;

#define DAY_SLASH_SEC 1.0f
#define MONTH_SLASH_SEC 30.5f
#define YEAR_SLASH_SEC 365.0f

int init_shader(ShaderManager *main, ShaderManager *skybox)
{
	int result;
	Shader main_sh[2], skybox_sh[2];

	// =========== Vertex shader ===========
	result = main_sh[0].Compile("main.vs", GL_VERTEX_SHADER);
	if(result) {
		fprintf(stderr, "\"main.vs\": %s\n", main_sh[0].GetError());
		return 1;
	}
	result = skybox_sh[0].Compile("skybox.vs", GL_VERTEX_SHADER);
	if(result) {
		fprintf(stderr, "\"skybox.vs\": %s\n", skybox_sh[0].GetError());
		return 1;
	}

	// =========== Fragment shader ===========
	result = main_sh[1].Compile("main.frag", GL_FRAGMENT_SHADER);
	if(result) {
		fprintf(stderr, "\"main.frag\": %s\n", main_sh[1].GetError());
		return 1;
	}
	result = skybox_sh[1].Compile("skybox.frag", GL_FRAGMENT_SHADER);
	if(result) {
		fprintf(stderr, "\"skybox.frag\": %s\n", skybox_sh[1].GetError());
		return 1;
	}

	// =========== Link shaders in Manager ===========
	result = main->Link(main_sh, 2);
	if(result)
		return 1;
	result = skybox->Link(skybox_sh, 2);
	if(result)
		return 1;

	return 0;
}

CelestialObject *init_solar_system()
{
	Texture *sun_texture = new Texture(GL_TEXTURE_2D);
	sun_texture->LoadImage("content/sun.jpg");
	CelestialObject *sun = new CelestialObject(sun_texture);
	sun->SetPeriod(0.0f, 25.37f);
	sun->SetRadius(5.0f, 0.0f);
	sun->SetTilts(7.25f, 0.0f);

	Texture *mercury_texture = new Texture(GL_TEXTURE_2D);
	mercury_texture->LoadImage("content/mercury.jpg");
	CelestialObject *mercury = new CelestialObject(mercury_texture);
	mercury->SetPeriod(87.97f, 58.64f);
	mercury->SetRadius(0.38f, 6.9f);
	mercury->SetTilts(0.01f, 7.01f);

	Texture *venus_texture = new Texture(GL_TEXTURE_2D);
	venus_texture->LoadImage("content/venus.jpg");
	CelestialObject *venus = new CelestialObject(venus_texture);
	venus->SetPeriod(224.7f, -243.01);
	venus->SetRadius(0.95f, 13.8f);
	venus->SetTilts(177.36f, 3.39f);

	Texture *earth_texture = new Texture(GL_TEXTURE_2D);
	earth_texture->LoadImage("content/earth.jpg");
	CelestialObject *earth = new CelestialObject(earth_texture);
	earth->SetPeriod(365.25f, 1.0f);
	earth->SetRadius(1.0f, 20.7f);
	earth->SetTilts(23.0f, 0.0f);

	Texture *moon_texture = new Texture(GL_TEXTURE_2D);
	moon_texture->LoadImage("content/moon.jpg");
	CelestialObject *moon = new CelestialObject(moon_texture);
	moon->SetPeriod(27.32f, 27.32f);
	moon->SetRadius(0.1f, 0.5f);
	moon->SetTilts(1.54f, 23.45f);

	Texture *mars_texture = new Texture(GL_TEXTURE_2D);
	mars_texture->LoadImage("content/mars.jpg");
	CelestialObject *mars = new CelestialObject(mars_texture);
	mars->SetPeriod(686.98f, 1.02f);
	mars->SetRadius(0.53f, 31.05f);
	mars->SetTilts(25.19f, 1.85f);

	Texture *jupiter_texture = new Texture(GL_TEXTURE_2D);
	jupiter_texture->LoadImage("content/jupiter.jpg");
	CelestialObject *jupiter = new CelestialObject(jupiter_texture);
	jupiter->SetPeriod(365.25f * 11.86f, 0.41f);
	jupiter->SetRadius(4.8f, 93.15f);
	jupiter->SetTilts(3.13f, 1.31f);

	Texture *saturn_texture = new Texture(GL_TEXTURE_2D);
	saturn_texture->LoadImage("content/saturn.jpg");
	CelestialObject *saturn = new CelestialObject(saturn_texture);
	saturn->SetPeriod(365.25f * 29.46f, 0.44f);
	saturn->SetRadius(4.5f, 172.32f);
	saturn->SetTilts(26.73f, 2.49f);

	Texture *uranus_texture = new Texture(GL_TEXTURE_2D);
	uranus_texture->LoadImage("content/uranus.jpg");
	CelestialObject *uranus = new CelestialObject(uranus_texture);
	uranus->SetPeriod(365.25f * 84.02f, -0.71f);
	uranus->SetRadius(4.0f, 244.65f);
	uranus->SetTilts(97.77f, 0.77f);

	Texture *neptune_texture = new Texture(GL_TEXTURE_2D);
	neptune_texture->LoadImage("content/neptune.jpg");
	CelestialObject *neptune = new CelestialObject(neptune_texture);
	neptune->SetPeriod(365.25f * 168.78f, 0.67f);
	neptune->SetRadius(3.88f, 517.0f);
	neptune->SetTilts(28.32f, 1.77f);

	/* set dependencies: master to slave */
	sun->AddSlave(mercury);
	sun->AddSlave(venus);
	sun->AddSlave(earth);
	earth->AddSlave(moon);
	sun->AddSlave(mars);
	sun->AddSlave(jupiter);
	sun->AddSlave(saturn);
	sun->AddSlave(uranus);
	sun->AddSlave(neptune);
	return sun;
}

int main(int argc, char *argv[])
{
	int window_width = 1280;
	int window_height = 720;
	int result;
	result = Application::Init();
	if(result) {
		fprintf(stderr, "Error: application initialization failed\n");
		return 1;
	}

	Window *game_window;
	ShaderManager main_shader;
	ShaderManager skybox_shader;

	game_window = Window::Initialize(
		window_width, window_height, "Space Simulator");
	if(!game_window) {
		fprintf(stderr, "Error: window initialization failed\n");
		Application::Terminate();
		return 1;
	}
	game_window->MakeContextCurrent();

	result = init_shader(&main_shader, &skybox_shader);
	if(result) {
		fprintf(stderr, "Error: shader initialization failed\n");
		Application::Terminate();
		return 1;
	}

	Events game_events(game_window);
	EventsManager::AddListener(&game_events, EM_LISTEN_KEY | EM_LISTEN_CURSOR |
		EM_LISTEN_MBUTTON | EM_LISTEN_WINDOWSIZE | EM_LISTEN_MSCROLL);

	// =========== load skybox ===========
	const char *skybox_images[] = {
		"content/skybox_right.jpg",
		"content/skybox_left.jpg",
		"content/skybox_top.jpg",
		"content/skybox_bottom.jpg",
		"content/skybox_front.jpg",
		"content/skybox_back.jpg"
	};

	Texture skybox_texture(GL_TEXTURE_CUBE_MAP);
	result = skybox_texture.LoadImage(skybox_images);
	if(result) {
		fprintf(stderr, "Error: skybox load failed\n");
		Application::Terminate();
		return 1;
	}

	// =========== create objects ===========
	Mesh *object_cube = form_cube();

	CelestialObject::InitializeMesh();
	CelestialObject *sun = init_solar_system();

	// =========== shader context =========== 
	mat4 proj_view(1.0f);
	
	Camera cam(vec3(0.0f, 10.0f, 40.0f));
	cam.SetSpeed(30.0f);
	cam.SetPerspective(45.0f, 0.1f, 1000.0f);

	GLuint modelLoc, proj_viewLoc, skyboxLoc;
	modelLoc = glGetUniformLocation(main_shader.GetID(), "model");
	proj_viewLoc = glGetUniformLocation(main_shader.GetID(), "proj_view");
	skyboxLoc = glGetUniformLocation(skybox_shader.GetID(), "proj_view");

	// =========== pre game loop ===========
	#ifdef WIREFRAME_MODE
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	#endif
	glEnable(GL_DEPTH_TEST);

	GLfloat deltaTime = 0.0f, lastFrame = 0.0f;

	// =========== game loop ===========
	while(!game_window->IsShouldClose()) {
		GLfloat currentFrame = Application::GetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		game_window->GetWinSize(window_width, window_height);

		// =========== handle input ===========
		EventsManager::PollEvents();
		if(game_events.Jpressed(KEY_ESCAPE))
			game_window->SetShouldClose(1);
		if(game_events.Jpressed(KEY_TAB))
			game_window->ToggleCursorMode();

		if(game_events.Pressed(KEY_W))
			cam.Movement(FORWARD, deltaTime);
		if(game_events.Pressed(KEY_S))
			cam.Movement(BACKWARD, deltaTime);
		if(game_events.Pressed(KEY_A))
			cam.Movement(LEFT, deltaTime);
		if(game_events.Pressed(KEY_D))
			cam.Movement(RIGHT, deltaTime);

		float delta_x = game_events.GetDX();
		float delta_y = game_events.GetDY();
		if(delta_x || delta_y)
			cam.UpdateView(delta_x, delta_y);

		delta_y = game_events.GetScrollDY();
		if(delta_y)
			cam.UpdateFov(delta_y);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// =========== draw skybox ===========
		glDepthMask(GL_FALSE);
			skybox_shader.Use();
			skybox_texture.Bind();

			proj_view = cam.GetSkyboxMatrix(window_width, window_height);
			glUniformMatrix4fv(skyboxLoc, 1, GL_FALSE, value_ptr(proj_view));
			object_cube->Draw();
		glDepthMask(GL_TRUE);

		// =========== draw space objects ===========
		main_shader.Use();

		proj_view = cam.GetProjViewMatrix(window_width, window_height);
		glUniformMatrix4fv(proj_viewLoc, 1, GL_FALSE, value_ptr(proj_view));
		sun->Draw(lastFrame, MONTH_SLASH_SEC, modelLoc);

		game_window->SwapBuffers();
	}

	delete object_cube;
	delete game_window;
	Application::Terminate();
	return 0;
}
