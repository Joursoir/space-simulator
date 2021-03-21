#ifndef ENGINE_EVENTS_H
#define ENGINE_EVENTS_H

#define MAX_KEYS GLFW_KEY_LAST + 1 + GLFW_MOUSE_BUTTON_LAST + 1
#define MOUSE_BUTTONS GLFW_KEY_LAST + 1 /* when start mouse buttons */

class Events {
	bool *keys;
	unsigned int *frames;
	unsigned int cur_frame;
	bool update_frame;
	float delta_x;
	float delta_y;
	float x;
	float y;
	bool cursor_locked;
	
public:
	Events();
	~Events();

	bool Pressed(int keycode);
	bool Jpressed(int keycode);
	bool Clicked(int button);
	bool Jclicked(int button);

	void NextFrame();
	void KeyHandle(int key, int scancode, int action, int mode);
	void CursorPosHandle(double xpos, double ypos);
	void MouseButtonHandle(int button, int action, int mode);
};

#endif /* ENGINE_EVENTS_H */
