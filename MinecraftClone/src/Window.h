#pragma once

struct WindowProps
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
	Window(const WindowProps& props = WindowProps());
	~Window();

	bool shouldClose();
	void pollEvents();
	void swapBuffers();
private:
	GLFWwindow* window;
};
