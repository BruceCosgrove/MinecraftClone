#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float near, float far)
	: fov(fov), near(near), far(far)
{
	
}

void Camera::onViewportResize(int width, int height)
{
	aspectRatio = (float)width / (float)height;
	recalculate();
}

void Camera::recalculate()
{
	projection = glm::perspective(fov, aspectRatio, near, far);
}
