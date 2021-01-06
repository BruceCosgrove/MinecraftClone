#pragma once

struct WindowSpecifications
{
	int width = 1280;
	int height = 720;
	const char* title = "Minecraft Clone";
	bool vsync = true;
};

struct GLFWwindow;
class Window
{
public:
	Window(const WindowSpecifications& specs = WindowSpecifications());
	~Window();

	bool shouldClose();
	void pollEvents();
	void swapBuffers();
	
	inline GLFWwindow* getNativeWindow() const { return window; }
private:
	GLFWwindow* window = nullptr;
};
