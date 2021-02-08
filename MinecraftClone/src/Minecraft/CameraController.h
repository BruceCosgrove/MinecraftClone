#pragma once

#include "Events/Event.h"

#include <glm/glm.hpp>

class CameraController
{
public:
	CameraController() = default;

	void onUpdate(float deltaTime);
	void onEvent(const Event& event);

	glm::mat4 getTransform() const;

	void setTranslation(const glm::vec3& translation) { this->translation = translation; }
	void setRotation(const glm::vec3& rotation) { this->rotation = rotation; }
private:
	float speed = 1.0f;

	float lastMouseX = 0.0f;
	float lastMouseY = 0.0f;
	float mouseDX = 0.0f;
	float mouseDY = 0.0f;

	const float maxPitch = glm::radians(90.0f);
	const float minPitch = -maxPitch;

	glm::vec3 translation{ 0.0f };
	glm::vec3 rotation{ 0.0f };
};
