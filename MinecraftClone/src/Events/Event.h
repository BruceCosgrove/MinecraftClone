#pragma once

#include <string>

enum class EventType
{
	WindowClose, WindowResize, WindowMove, WindowFocus, WindowMinimize, WindowMaximize, 
		WindowDrop, WindowFramebufferResize, WindowContentScale, WindowRefresh,
	KeyPress, KeyRepeat, KeyRelease, KeyChar,
	MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll, MouseEnter,
	JoystickConnect, MonitorConnect
};

class Event
{
public:
	Event(EventType type)
		: type(type) {}
	virtual ~Event() = default;

	inline EventType getType() const { return type; }
	virtual std::string toString() const = 0;

	inline bool isHandled() const { return handled; }
	inline void handle() const { handled = true; }
private:
	EventType type;
	mutable bool handled = false;
};
