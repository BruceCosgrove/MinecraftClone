#include "CameraController.h"

#include "IO/Input.h"
#include "Events/MouseEvents.h"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

void CameraController::onUpdate(float deltaTime)
{
	const float movementSpeed = 5.0f * deltaTime;

	const glm::vec3 forward = movementSpeed * glm::vec3(cosf(rotation.y), 0.0f, sinf(rotation.y));
	const glm::vec3 left = glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f));

	if (Input::isKeyPressed(Keycode::W)) { translation.z -= forward.x; translation.x -= forward.z; }
	if (Input::isKeyPressed(Keycode::S)) { translation.z += forward.x; translation.x += forward.z; }
	if (Input::isKeyPressed(Keycode::A)) { translation.x -= left.z; translation.z -= left.x; }
	if (Input::isKeyPressed(Keycode::D)) { translation.x += left.z; translation.z += left.x; }
	if (Input::isKeyPressed(Keycode::LeftShift)) translation.y -= movementSpeed;
	if (Input::isKeyPressed(Keycode::Space)) translation.y += movementSpeed;

	if (Input::isMouseButtonPressed(Mousecode::MBLeft))
	{
		const float rotationSpeed = 0.2f * deltaTime;

		rotation.y -= mouseDX * rotationSpeed;
		rotation.x = std::min(std::max(rotation.x - mouseDY * rotationSpeed, minPitch), maxPitch);
		mouseDX = 0.0f;
		mouseDY = 0.0f;
	}
}

void CameraController::onEvent(const Event& event)
{
	if (event.getType() == EventType::MouseMove)
	{
		const MouseMoveEvent& mme = (const MouseMoveEvent&)event;
		float mouseX = mme.getX();
		float mouseY = mme.getY();
		mouseDX = mouseX - lastMouseX;
		mouseDY = mouseY - lastMouseY;
		lastMouseX = mouseX;
		lastMouseY = mouseY;
	}
}

glm::mat4 CameraController::getTransform() const
{
	return glm::translate(glm::mat4(1.0f), translation) * glm::toMat4(glm::quat(rotation));
}
