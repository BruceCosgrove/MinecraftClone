#pragma once

#include <memory>

#include "Core/Window.h"
#include "Core/ImGuiWrapper.h"
#include "Minecraft/Minecraft.h"

class Application
{
public:
	Application(const WindowSpecifications& windowSpecs = WindowSpecifications());
	~Application();

	inline static Application& get() { return *instance; }
	inline Window& getWindow() const { return *window; }
	inline Minecraft& getMinecraft() const { return *minecraft; }

	void run();
	void terminate();
private:
	void onEvent(const Event& event);

	static Application* instance;

	bool running = true;
	bool rendering = true;

	// Window needs to be deleted after everything else
	Window* window;
	ImGuiWrapper* imguiWrapper;
	Minecraft* minecraft;
};
