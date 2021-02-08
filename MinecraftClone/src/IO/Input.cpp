#include "Input.h"

#include "Core/Application.h"
#include <glfw/glfw3.h>

bool Input::isKeyPressed(Keycode keycode)
{
    auto window = Application::get().getWindow().getNativeWindow();
    return glfwGetKey(window, static_cast<int>(keycode)) == GLFW_PRESS;
}

bool Input::isKeyReleased(Keycode keycode)
{
    auto window = Application::get().getWindow().getNativeWindow();
    return glfwGetKey(window, static_cast<int>(keycode)) == GLFW_RELEASE;
}

bool Input::isMouseButtonPressed(Mousecode button)
{
    auto window = Application::get().getWindow().getNativeWindow();
    return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_PRESS;
}

bool Input::isMouseButtonReleased(Mousecode button)
{
    auto window = Application::get().getWindow().getNativeWindow();
    return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_RELEASE;
}

std::pair<float, float> Input::getMousePos()
{
    auto window = Application::get().getWindow().getNativeWindow();
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return { (float)x, (float)y };
}

float Input::getMousePosX()
{
    auto [x, y] = getMousePos();
    return x;
}

float Input::getMousePosY()
{
    auto [x, y] = getMousePos();
    return y;
}
