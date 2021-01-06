#pragma once

#include "Window.h"

class ImGuiWrapper
{
public:
	ImGuiWrapper(const Window& window);
	~ImGuiWrapper();

	void begin();
	void end();
private:
	void init();

	const Window& window;
};
