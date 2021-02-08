#include "Window.h"

#include <glfw/glfw3.h>

#include "Events/WindowEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/DeviceEvents.h"

#include <algorithm>
#include <iostream>

Window::Window(const WindowSpecifications& specs)
{
	if (glfwInit() != GLFW_TRUE) return;

	state.current.width = specs.width;
	state.current.height = specs.height;
	state.title = specs.title;
	state.resizable = specs.resizable;
	state.fullscreen = specs.fullscreen;

	// TODO: get these from specifications
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, state.resizable);

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

	// Calculate the offset needed for the window to be centered in the primary monitor
	state.current.x = (videoMode->width - state.current.width) / 2;
	state.current.y = (videoMode->height - state.current.height) / 2;

	if (state.fullscreen)
	{
		saveDimensions();
		state.current.x = 0;
		state.current.y = 0;
		state.current.width = videoMode->width;
		state.current.height = videoMode->height;
	}

	window = glfwCreateWindow(state.current.width, state.current.height, state.title, state.fullscreen ? primaryMonitor : nullptr, nullptr);
	if (window == nullptr) return;

	glfwSetWindowPos(window, state.current.x, state.current.y);
	glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
	
	context = new Context(window);

	setVSync(specs.vsync);
	setCaptureMouse(specs.captureMouse);

	glfwSetWindowUserPointer(window, &state);
	
	// Window Events
	glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.eventCallback(WindowCloseEvent());
	});
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.current.width = width;
		state.current.height = height;
		state.eventCallback(WindowResizeEvent(width, height));
	});
	glfwSetWindowPosCallback(window, [](GLFWwindow* window, int x, int y)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.current.x = x;
		state.current.y = y;
		state.eventCallback(WindowMoveEvent(x, y));
	});
	glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.eventCallback(WindowFocusEvent(focused == GLFW_TRUE));
	});
	glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.eventCallback(WindowMinimizeEvent(iconified == GLFW_TRUE));
	});
	glfwSetWindowMaximizeCallback(window, [](GLFWwindow* window, int maximized)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.eventCallback(WindowMaximizeEvent(maximized == GLFW_TRUE));
	});
	glfwSetDropCallback(window, [](GLFWwindow* window, int pathCount, const char** paths)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.eventCallback(WindowDropEvent(pathCount, paths));
	});
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.eventCallback(WindowFramebufferResizeEvent(width, height));
	});
	glfwSetWindowContentScaleCallback(window, [](GLFWwindow* window, float scaleX, float scaleY)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.eventCallback(WindowContentScaleEvent(scaleX, scaleY));
	});
	glfwSetWindowRefreshCallback(window, [](GLFWwindow* window)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.eventCallback(WindowRefreshEvent());
	});

	// Key Events
	glfwSetKeyCallback(window, [](GLFWwindow* window, int keycode, int scancode, int action, int mods)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		if (keycode != GLFW_KEY_UNKNOWN)
		{
			switch (action)
			{
				case GLFW_PRESS: state.eventCallback(KeyPressEvent(static_cast<Keycode>(keycode), mods)); break;
				case GLFW_REPEAT: state.eventCallback(KeyRepeatEvent(static_cast<Keycode>(keycode), mods)); break;
				case GLFW_RELEASE: state.eventCallback(KeyReleaseEvent(static_cast<Keycode>(keycode), mods)); break;
			}
		}
	});
	// GLFW has a bug where this doesn't get called when ctrl is pressed
	glfwSetCharModsCallback(window, [](GLFWwindow* window, unsigned int codepoint, int mods)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.eventCallback(KeyCharEvent(codepoint, mods));
	});

	// Mouse Events
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
			case GLFW_PRESS: state.eventCallback(MouseButtonPressEvent(static_cast<Mousecode>(button), mods)); break;
			case GLFW_RELEASE: state.eventCallback(MouseButtonReleaseEvent(static_cast<Mousecode>(button), mods)); break;
		}
	});
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.eventCallback(MouseMoveEvent((float)x, (float)y));
	});
	glfwSetScrollCallback(window, [](GLFWwindow* window, double offsetX, double offsetY)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.eventCallback(MouseScrollEvent((float)offsetX, (float)offsetY));
	});
	glfwSetCursorEnterCallback(window, [](GLFWwindow* window, int entered)
	{
		auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
		state.eventCallback(MouseEnterEvent(entered == GLFW_TRUE));
	});

	// Device Events
	glfwSetJoystickCallback([](int jid, int event)
	{
		// Big brain hacks
		//auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		//auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));

		//state.eventCallback(JoystickConnectEvent(jid, event == GLFW_CONNECTED));
	});

	glfwShowWindow(window);
}

Window::~Window()
{
	delete context;
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::swapBuffers()
{
	context->swapBuffers();
}

void Window::setTitle(const char* title)
{
	glfwSetWindowTitle(window, title);
	state.title = title;
}

void Window::setVSync(bool vsync)
{
	glfwSwapInterval((int)vsync);
	state.vsync = vsync;
}

void Window::setResizable(bool resizable)
{
	glfwSetWindowAttrib(window, GLFW_RESIZABLE, resizable);
	state.resizable = resizable;
}

void Window::setFullscreen(bool fullscreen)
{
	if (fullscreen)
	{
		// Can change videomode while fullscreen
		// Only cache this the first time
		if (!state.fullscreen)
			saveDimensions();

		// https://stackoverflow.com/questions/21421074/how-to-create-a-full-screen-window-on-the-current-monitor-with-glfw
		// Get the monitor that most of the window is on
		int largestOverlap = INT_MIN;
		GLFWmonitor* monitor = nullptr;

		int monitorCount;
		GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

		for (int i = 0; i < monitorCount; i++)
		{
			const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[i]);

			int monitorX, monitorY;
			glfwGetMonitorPos(monitors[i], &monitorX, &monitorY);

			int overlapX = std::max(0, std::min(state.current.x + state.current.width, monitorX + videoMode->width) - std::max(state.current.x, monitorX));
			int overlapY = std::max(0, std::min(state.current.y + state.current.height, monitorY + videoMode->height) - std::max(state.current.y, monitorY));
			int overlap = overlapX * overlapY;

			if (overlap > largestOverlap)
			{
				largestOverlap = overlap;
				monitor = monitors[i];
			}
		}

		const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window, monitor, 0, 0, videoMode->width, videoMode->height, GLFW_DONT_CARE);

		setVSync(getVSync());
	}
	else
		glfwSetWindowMonitor(window, nullptr, state.preFullscreen.x, state.preFullscreen.y, state.preFullscreen.width, state.preFullscreen.height, GLFW_DONT_CARE);

	state.fullscreen = fullscreen;
}

void Window::setCaptureMouse(bool captureMouse)
{
	glfwSetInputMode(window, GLFW_CURSOR, captureMouse ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	state.captureMouse = captureMouse;
}

void Window::saveDimensions()
{
	state.preFullscreen.x = state.current.x;
	state.preFullscreen.y = state.current.y;
	state.preFullscreen.width = state.current.width;
	state.preFullscreen.height = state.current.height;
}
