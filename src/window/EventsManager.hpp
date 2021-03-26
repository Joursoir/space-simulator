#ifndef ENGINE_EVENTSMANAGER_H
#define ENGINE_EVENTSMANAGER_H

class Events;

enum em_listen {
	EM_LISTEN_KEY = 1,
	EM_LISTEN_CURSOR = 2,
	EM_LISTEN_MBUTTON = 4,
	EM_LISTEN_WINDOWSIZE = 8,
	EM_LISTEN_MSCROLL = 16
};

struct lStorage {
	Events **list;
	GLFWwindow **win;
	int *listen_events;
	int max_n;
		
	lStorage(int n) : max_n(n)
	{
		int i;
		list = new Events*[n];
		win = new GLFWwindow*[n];
		listen_events = new int[n];
		for(i = 0; i < n; i++) {
			list[i] = 0;
			win[i] = 0;
			listen_events[i] = 0;
		}
	}

	~lStorage()
	{
		delete[] list;
		delete[] win;
		delete[] listen_events;
	}

	void Add(Events *e, GLFWwindow *w, int listen)
	{
		int i;
		for(i = 0; i < max_n; i++) {
			if(list[i] == 0) {
				list[i] = e;
				win[i] = w;
				listen_events[i] = listen;
				break;
			}
		}

		// realloc memory:
		Events **tmp_list = list;
		GLFWwindow **tmp_win = win;
		int *tmp_levents = listen_events;

		list = new Events*[max_n + 1];
		win = new GLFWwindow*[max_n + 1];
		listen_events = new int[max_n + 1];

		for(i = 0; i < max_n; i++) {
			list[i] = tmp_list[i];
			win[i] = tmp_win[i];
			listen_events[i] = tmp_levents[i];
		}
		list[max_n] = e;
		win[max_n] = w;
		tmp_levents[max_n] = listen;

		delete[] tmp_list;
		delete[] tmp_win;
		delete[] tmp_levents;
	}
};

class EventsManager {
	static struct lStorage listeners;

public:
	static void PollEvents();
	static void AddListener(Events *e, int listen);

private:
	EventsManager() { }

	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow *window, int button, int action, int mode);
	static void window_size_callback(GLFWwindow *window, int width, int height);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif /* ENGINE_EVENTSMANAGER_H */
