#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"

/* static method */
Window *Window::Initialize(int width, int height, const char *title)
{
	GLFWwindow *win;
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	/*glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwSetErrorCallback(error_callback);*/

	win = glfwCreateWindow(width, height, title, 0, 0);
	if(!win) {
		fprintf(stderr, "Failed to create GLFW window\n");
		return 0;
	}
	glfwMakeContextCurrent(win);

	glewExperimental = GL_TRUE;
	int result = glewInit();
	if(result != GLEW_OK) {
		fprintf(stderr, "Failed to init GLEW: %s\n", title);
		return 0;
	}

	Window *w = new Window(win, width, height);
	w->MakeContextCurrent();
	w->ToggleCursorMode();
	return w;
}

void Window::Resize(int w, int h)
{
	width = w;
	height = h;
	if(glfwGetCurrentContext() == win)
		glViewport(0, 0, width, height);
}

void Window::MakeContextCurrent()
{
	glfwMakeContextCurrent(win);
	glViewport(0, 0, width, height);
}

int Window::GetCursorMode()
{
	return glfwGetInputMode(win, GLFW_CURSOR);
}

void Window::ToggleCursorMode()
{
	int mode = GetCursorMode() == GLFW_CURSOR_NORMAL ?
		GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
	glfwSetInputMode(win, GLFW_CURSOR, mode);
}

bool Window::IsShouldClose()
{
	return glfwWindowShouldClose(win);
}

void Window::SetShouldClose(int flag)
{
	glfwSetWindowShouldClose(win, flag);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(win);
}
