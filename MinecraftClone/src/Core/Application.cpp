#include "Application.h"

#include "Rendering/Renderer.h"
#include "Events/WindowEvents.h"

#define BIND_FUNC(func) [this](auto&&... args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); }

Application* Application::instance = nullptr;

Application::Application(const WindowSpecifications& windowSpecs)
{
	instance = this;

	window = new Window(windowSpecs);
	window->setEventCallback(BIND_FUNC(onEvent));

	imguiWrapper = new ImGuiWrapper(*window);

	Renderer::init();

	minecraft = new Minecraft();
}

Application::~Application()
{
	delete minecraft;
	delete imguiWrapper;

	Renderer::shutdown();
	delete window;
}

void Application::run()
{
	while (running)
	{
		float deltaTime = window->getContext()->getElapsedTime();
		minecraft->onUpdate(deltaTime);

		if (rendering)
		{
			minecraft->onRender();
			imguiWrapper->begin();
			minecraft->onImGuiRender();
			imguiWrapper->end();
		}

		window->pollEvents();

		if (rendering)
			window->swapBuffers();
	}
}

void Application::terminate()
{
	running = false;
}

void Application::onEvent(const Event& event)
{
	switch (event.getType())
	{
		case EventType::WindowClose:
		{
			terminate();
			event.handle();
			break;
		}
		case EventType::WindowResize:
		{
			const WindowResizeEvent& wre = (const WindowResizeEvent&)event;
			if (wre.getWidth() == 0 || wre.getHeight() == 0)
			{
				rendering = false;
				event.handle();
			}
			else
			{
				rendering = true;
				Renderer::onViewportResized(wre.getWidth(), wre.getHeight());
			}
			break;
		}
		case EventType::WindowMinimize:
		{
			const WindowMinimizeEvent& wme = (const WindowMinimizeEvent&)event;
			rendering = !wme.isMinimized();
			break;
		}
	}

	if (!event.isHandled())
		minecraft->onEvent(event);
}
