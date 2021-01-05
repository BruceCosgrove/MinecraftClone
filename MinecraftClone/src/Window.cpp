#include "Window.h"

#include <gl/glew.h>
#include <glfw/glfw3.h>

Window::Window(const WindowProps& props)
{
	if (glfwInit() != GLFW_TRUE)
		return;

	window = glfwCreateWindow(props.width, props.height, props.title, nullptr, nullptr);
	if (window == nullptr)
		return;

	glfwMakeContextCurrent(window);
	glfwSwapInterval(props.vsync);

	// Initialize glew AFTER a valid opengl context is made current
	if (glewInit() != GLEW_OK)
		return;
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}
