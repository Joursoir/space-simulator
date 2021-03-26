#include <stdio.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "EventsManager.hpp"
#include "Events.hpp"

struct lStorage EventsManager::listeners(2);

void EventsManager::PollEvents()
{
	int max = listeners.max_n, i;
	for(i = 0; i < max; i++) {
		if(!listeners.list[i])
			continue;

		listeners.list[i]->NextFrame();
	}
	glfwPollEvents();
}

void EventsManager::AddListener(Events *e, int listen)
{
	if(listen <= 0)
		return;

	GLFWwindow *win = e->GetWindow()->GetWin();
	if(listen & EM_LISTEN_KEY)
		glfwSetKeyCallback(win, key_callback);
	if(listen & EM_LISTEN_CURSOR)
		glfwSetCursorPosCallback(win, cursor_pos_callback);
	if(listen & EM_LISTEN_MBUTTON)
		glfwSetMouseButtonCallback(win, mouse_button_callback);
	if(listen & EM_LISTEN_WINDOWSIZE)
		glfwSetWindowSizeCallback(win, window_size_callback);
	if(listen & EM_LISTEN_MSCROLL)
		glfwSetScrollCallback(win, scroll_callback);

	listeners.Add(e, win, listen);
}

//////////////////////////////////////////////////////////////////////////////

void EventsManager::key_callback(GLFWwindow *window, int key, int scancode,
	int action, int mode)
{
	int max = listeners.max_n, i;
	for(i = 0; i < max; i++) {
		if(!listeners.list[i])
			continue;
		if(!(listeners.listen_events[i] & EM_LISTEN_KEY))
			continue;
		if(listeners.win[i] != window)
			continue;

		//fprintf(stderr, "key_callback\n");
		listeners.list[i]->KeyHandle(key, scancode, action, mode);
	}
}

void EventsManager::cursor_pos_callback(GLFWwindow *window, double xpos,
	double ypos)
{
	int max = listeners.max_n, i;
	for(i = 0; i < max; i++) {
		if(!listeners.list[i])
			continue;
		if(!(listeners.listen_events[i] & EM_LISTEN_CURSOR))
			continue;
		if(listeners.win[i] != window)
			continue;

		//fprintf(stderr, "cursor_pos_callback\n");
		listeners.list[i]->CursorPosHandle(xpos, ypos);
	}
}

void EventsManager::mouse_button_callback(GLFWwindow *window, int button,
	int action, int mode)
{
	int max = listeners.max_n, i;
	for(i = 0; i < max; i++) {
		if(!listeners.list[i])
			continue;
		if(!(listeners.listen_events[i] & EM_LISTEN_MBUTTON))
			continue;
		if(listeners.win[i] != window)
			continue;

		//fprintf(stderr, "mouse_button_callback\n");
		listeners.list[i]->MouseButtonHandle(button, action, mode);
	}
}

void EventsManager::window_size_callback(GLFWwindow* window,
	int width, int height)
{
	int max = listeners.max_n, i;
	for(i = 0; i < max; i++) {
		if(!listeners.list[i])
			continue;
		if(!(listeners.listen_events[i] & EM_LISTEN_WINDOWSIZE))
			continue;
		if(listeners.win[i] != window)
			continue;

		//fprintf(stderr, "window_size_callback\n");
		listeners.list[i]->WindowResizeHandle(width, height);
	}
}

void EventsManager::scroll_callback(GLFWwindow* window,
	double xoffset, double yoffset)
{
	int max = listeners.max_n, i;
	for(i = 0; i < max; i++) {
		if(!listeners.list[i])
			continue;
		if(!(listeners.listen_events[i] & EM_LISTEN_MSCROLL))
			continue;
		if(listeners.win[i] != window)
			continue;

		//fprintf(stderr, "scroll_callback\n");
		listeners.list[i]->MouseScrollHandle(xoffset, yoffset);
	}
}
