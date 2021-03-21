#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Events.hpp"

Events::Events() : cur_frame(0), delta_x(0.0), delta_y(0.0),
	x(0.0), y(0.0), cursor_locked(false)
{
	keys = new bool[MAX_KEYS];
	memset(keys, false, MAX_KEYS * sizeof(bool));
	frames = new unsigned int[MAX_KEYS];
	memset(frames, 0, MAX_KEYS * sizeof(unsigned int));
}

Events::~Events()
{
	delete[] keys;
	delete[] frames;
}

bool Events::Pressed(int keycode)
{
	if(keycode < 0 || keycode >= MOUSE_BUTTONS)
		return false;
	return keys[keycode];
}

bool Events::Jpressed(int keycode)
{
	if(keycode < 0 || keycode >= MOUSE_BUTTONS)
		return false;
	return keys[keycode] && (frames[keycode] == cur_frame);
}

bool Events::Clicked(int button)
{
	return keys[MOUSE_BUTTONS + button];
}

bool Events::Jclicked(int button)
{
	int idx = MOUSE_BUTTONS + button;
	return keys[idx] && (frames[idx] == cur_frame);
}

void Events::NextFrame()
{
	cur_frame++;
}

//////////////////////////////////////////////////////////////////////////////

void Events::KeyHandle(int key, int scancode, int action, int mode)
{
	if(action == GLFW_PRESS) {
		keys[key] = true;
		frames[key] = cur_frame;
	}
	else if(action == GLFW_RELEASE) {
		keys[key] = false;
		frames[key] = cur_frame;
	}
}

void Events::CursorPosHandle(double xpos, double ypos)
{
	delta_x = xpos - x;
	delta_y = ypos - y;

	x = xpos;
	y = ypos;
}

void Events::MouseButtonHandle(int button, int action, int mode)
{
	if(action == GLFW_PRESS) {
		keys[MOUSE_BUTTONS + button] = true;
		frames[MOUSE_BUTTONS + button] = cur_frame;
	}
	else if (action == GLFW_RELEASE){
		keys[MOUSE_BUTTONS + button] = false;
		frames[MOUSE_BUTTONS + button] = cur_frame;
	}
}
