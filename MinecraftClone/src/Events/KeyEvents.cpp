#include "KeyEvents.h"
#include <sstream>

KeyPressEvent::KeyPressEvent(Keycode keycode, int mods)
	: Event(EventType::KeyPress), keycode(keycode), mods(mods)
{

}

std::string KeyPressEvent::toString() const
{
	std::stringstream stream;
	stream << "KeyPressEvent: keycode=" << static_cast<unsigned short>(keycode) << " mods=" << mods;
	return stream.str();
}

KeyRepeatEvent::KeyRepeatEvent(Keycode keycode, int mods)
	: Event(EventType::KeyRepeat), keycode(keycode), mods(mods)
{

}

std::string KeyRepeatEvent::toString() const
{
	std::stringstream stream;
	stream << "KeyRepeatEvent: keycode=" << static_cast<unsigned short>(keycode) << " mods=" << mods;
	return stream.str();
}

KeyReleaseEvent::KeyReleaseEvent(Keycode keycode, int mods)
	: Event(EventType::KeyRelease), keycode(keycode), mods(mods)
{

}

std::string KeyReleaseEvent::toString() const
{
	std::stringstream stream;
	stream << "KeyReleaseEvent: keycode=" << static_cast<unsigned short>(keycode) << " mods=" << mods;
	return stream.str();
}

KeyCharEvent::KeyCharEvent(unsigned int codepoint, int mods)
	: Event(EventType::KeyChar), codepoint(codepoint), mods(mods)
{

}

std::string KeyCharEvent::toString() const
{
	std::stringstream stream;
	stream << "KeyCharEvent: codepoint=" << codepoint << " mods=" << mods;
	return stream.str();
}
