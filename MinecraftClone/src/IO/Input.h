#pragma once

#include <utility>

#include "Core/Keycodes.h"
#include "Core/Mousecodes.h"

class Input
{
public:
	static bool isKeyPressed(Keycode keycode);
	static bool isKeyReleased(Keycode keycode);

	static bool isMouseButtonPressed(Mousecode button);
	static bool isMouseButtonReleased(Mousecode button);

	static std::pair<float, float> getMousePos();
	static float getMousePosX();
	static float getMousePosY();
};
