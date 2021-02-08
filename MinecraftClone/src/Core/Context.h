#pragma once

struct GLFWwindow;
class Context
{
public:
	Context(GLFWwindow* window);

	void swapBuffers();

	float getElapsedTime() const;
private:
	GLFWwindow* window;
	mutable float lastTime = 0.0f;
};
