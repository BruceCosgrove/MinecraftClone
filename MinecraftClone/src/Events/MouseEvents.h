#pragma once

#include "Event.h"
#include "Core/Mousecodes.h"

class MouseButtonPressEvent : public Event
{
public:
	MouseButtonPressEvent(Mousecode button, int mods);

	inline Mousecode getButton() const { return button; }
	inline int getMods() const { return mods; }

	virtual std::string toString() const override;
private:
	Mousecode button;
	int mods;
};

class MouseButtonReleaseEvent : public Event
{
public:
	MouseButtonReleaseEvent(Mousecode button, int mods);

	inline Mousecode getButton() const { return button; }
	inline int getMods() const { return mods; }

	virtual std::string toString() const override;
private:
	Mousecode button;
	int mods;
};

class MouseMoveEvent : public Event
{
public:
	MouseMoveEvent(float x, float y);

	inline float getX() const { return x; }
	inline float getY() const { return y; }

	virtual std::string toString() const override;
private:
	float x;
	float y;
};

class MouseScrollEvent : public Event
{
public:
	MouseScrollEvent(float offsetX, float offsetY);

	inline float getOffsetX() const { return offsetX; }
	inline float getOffsetY() const { return offsetY; }

	virtual std::string toString() const override;
private:
	float offsetX;
	float offsetY;
};

class MouseEnterEvent : public Event
{
public:
	MouseEnterEvent(bool enter);

	inline bool hasEntered() const { return enter; }

	virtual std::string toString() const override;
private:
	bool enter;
};
