#pragma once

#include "Event.h"

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent();

	virtual std::string toString() const override;
};

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(int width, int height);

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

	virtual std::string toString() const override;
private:
	int width;
	int height;
};

class WindowMoveEvent : public Event
{
public:
	WindowMoveEvent(int x, int y);

	inline int getX() const { return x; }
	inline int getY() const { return y; }

	virtual std::string toString() const override;
private:
	int x;
	int y;
};

class WindowFocusEvent : public Event
{
public:
	WindowFocusEvent(bool focus);

	inline bool isFocused() const { return focus; }

	virtual std::string toString() const override;
private:
	bool focus;
};

class WindowMinimizeEvent : public Event
{
public:
	WindowMinimizeEvent(bool minimize);

	inline bool isMinimized() const { return minimize; }

	virtual std::string toString() const override;
private:
	bool minimize;
};

class WindowMaximizeEvent : public Event
{
public:
	WindowMaximizeEvent(bool maximize);

	inline bool isMaximized() const { return maximize; }

	virtual std::string toString() const override;
private:
	bool maximize;
};

class WindowDropEvent : public Event
{
public:
	WindowDropEvent(int pathCount, const char** paths);
	~WindowDropEvent();

	inline int getPathCount() const { return pathCount; }
	inline char** getPaths() const { return paths; }

	virtual std::string toString() const override;
private:
	int pathCount;
	char** paths;
};

class WindowFramebufferResizeEvent : public Event
{
public:
	WindowFramebufferResizeEvent(int width, int height);

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

	virtual std::string toString() const override;
private:
	int width;
	int height;
};

class WindowContentScaleEvent : public Event
{
public:
	WindowContentScaleEvent(float scaleX, float scaleY);

	inline float getScaleX() const { return scaleX; }
	inline float getScaleY() const { return scaleY; }

	virtual std::string toString() const override;
private:
	float scaleX;
	float scaleY;
};

class WindowRefreshEvent : public Event
{
public:
	WindowRefreshEvent();

	virtual std::string toString() const override;
};
