#pragma once

#include <functional>

#include "Context.h"
#include "Events/Event.h"

struct WindowSpecifications
{
	int width = 1280;
	int height = 720;
	const char* title = "Minecraft Clone";
	bool vsync = true;
	bool resizable = true;
	bool fullscreen = false;
	bool captureMouse = false;
};

struct GLFWwindow;
class Window
{
public:
	Window(const WindowSpecifications& specs = WindowSpecifications());
	~Window();

	void pollEvents();
	void swapBuffers();
	
	inline int getWidth() const { return state.current.width; }
	inline int getHeight() const { return state.current.height; }

	const char* getTitle() const { return state.title; }
	void setTitle(const char* title);

	inline bool getVSync() const { return state.vsync; }
	void setVSync(bool vsync);
	inline void toggleVSync() { setVSync(!getVSync()); }

	inline bool getResizable() const { return state.resizable; }
	void setResizable(bool resizable);
	inline void toggleResizable() { setResizable(!getResizable()); }

	inline bool getFullscreen() const { return state.fullscreen; }
	void setFullscreen(bool fullscreen);
	inline void toggleFullscreen() { setFullscreen(!getFullscreen()); }

	inline bool getCaptureMouse() const { return state.captureMouse; }
	void setCaptureMouse(bool captureMouse);
	inline void toggleCaptureMouse() { setCaptureMouse(!getCaptureMouse()); }

	inline GLFWwindow* getNativeWindow() const { return window; }
	inline Context* getContext() const { return context; }

	using EventCallbackFunc = std::function<void(const Event&)>;
	inline void setEventCallback(const EventCallbackFunc& callback) { state.eventCallback = callback; }
private:
	void saveDimensions();

	GLFWwindow* window = nullptr;
	Context* context = nullptr;

	struct WindowState
	{
		struct
		{
			int x = 0;
			int y = 0;
			int width = 0;
			int height = 0;
		} current, preFullscreen;

		const char* title = nullptr;
		bool vsync = false;
		bool resizable = false;
		bool fullscreen = false;
		bool captureMouse = false;

		EventCallbackFunc eventCallback;
	} state;
};
