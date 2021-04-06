#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

class Application {
	Application() { }
public:
	static int Init();
	static void Terminate();
	static void SwapInterval(int interval);
	static float GetTime();
};

#endif /* ENGINE_APPLICATION_H */
