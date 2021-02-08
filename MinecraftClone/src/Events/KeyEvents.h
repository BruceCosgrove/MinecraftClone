#pragma once

#include "Event.h"
#include "Core/Keycodes.h"

class KeyPressEvent : public Event
{
public:
	KeyPressEvent(Keycode keycode, int mods);

	inline Keycode getKeycode() const { return keycode; }
	inline int getMods() const { return mods; }

	virtual std::string toString() const override;
private:
	Keycode keycode;
	int mods;
};

class KeyRepeatEvent : public Event
{
public:
	KeyRepeatEvent(Keycode keycode, int mods);

	inline Keycode getKeycode() const { return keycode; }
	inline int getMods() const { return mods; }

	virtual std::string toString() const override;
private:
	Keycode keycode;
	int mods;
};

class KeyReleaseEvent : public Event
{
public:
	KeyReleaseEvent(Keycode keycode, int mods);

	inline Keycode getKeycode() const { return keycode; }
	inline int getMods() const { return mods; }

	virtual std::string toString() const override;
private:
	Keycode keycode;
	int mods;
};

class KeyCharEvent : public Event
{
public:
	KeyCharEvent(unsigned int codepoint, int mods);

	inline unsigned int getCodepoint() const { return codepoint; }
	inline int getMods() const { return mods; }

	virtual std::string toString() const override;
private:
	unsigned int codepoint;
	int mods;
};
