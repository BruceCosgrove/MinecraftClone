#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera() = default;
	Camera(float fov, float near, float far);

	inline const glm::mat4& getProjection() const { return projection; }

	void onViewportResize(int width, int height);
private:
	void recalculate();

	float aspectRatio = 1.0f;
	float fov = 1.0f;
	float near = 0.1f;
	float far = 1.0f;
	glm::mat4 projection{ 1.0f };
};
