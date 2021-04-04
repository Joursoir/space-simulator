#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

class GLFWwindow;

class Window {
	GLFWwindow *win;
	int width, height;

	Window(GLFWwindow *a_win, int a_w, int a_h) : win(a_win),
		width(a_w), height(a_h) { }
public:
	~Window() { }
	GLFWwindow *GetWin() { return win; }

	static Window *Initialize(int width, int height, const char *title);

	void Resize(int w, int h);
	void MakeContextCurrent();
	int GetCursorMode();
	void ToggleCursorMode();
	bool IsShouldClose();
	void SetShouldClose(int flag);
	void SwapBuffers();
};

#endif /* ENGINE_WINDOW_H */
