#include "Window.h"

#include <gl/glew.h>
#include <glfw/glfw3.h>

//#include <iostream>

Window::Window(const WindowSpecifications& specs)
{
	if (glfwInit() != GLFW_TRUE)
		return;

	// TODO: get these from specifications
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(specs.width, specs.height, specs.title, nullptr, nullptr);
	if (window == nullptr)
		return;

	glfwMakeContextCurrent(window);
	glfwSwapInterval(specs.vsync);

	// Initialize glew AFTER a valid opengl context is made current
	if (glewInit() != GLEW_OK)
		return;
	
	//std::cout << glGetString(GL_VERSION) << '\n';
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
