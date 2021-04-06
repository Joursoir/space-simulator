#include <GLFW/glfw3.h>

#include "Application.hpp"

int Application::Init()
{
	return glfwInit() == GLFW_TRUE ? 0 : 1;
}

void Application::Terminate()
{
	glfwTerminate();
}

void Application::SwapInterval(int interval)
{
	glfwSwapInterval(interval);
}

GLfloat Application::GetTime()
{
	return glfwGetTime();
}
