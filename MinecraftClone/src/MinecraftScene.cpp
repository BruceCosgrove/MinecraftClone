#include "MinecraftScene.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

MinecraftScene::MinecraftScene()
{
	localTexture.reset(new Texture("resources/textures/sapling_oak.png", 4, true));
	texture.reset(new OpenGLTexture(localTexture.get()));
}

MinecraftScene::~MinecraftScene()
{

}

void MinecraftScene::onUpdate(float deltaTime)
{

}

void MinecraftScene::onRender(BasicRenderer& renderer)
{
	Vertex vertices[] = {
		{ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
		{ {  0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
		{ {  0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
		{ { -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,

		//4, 5, 6,
		//6, 7, 4,
	};

	renderer.beginScene(glm::mat4(1.0f), glm::mat4(1.0f));
	renderer.submit(sizeof(vertices) / sizeof(Vertex), vertices, sizeof(indices) / sizeof(unsigned int), indices, transform, texture.get());
	renderer.endScene();
}

void MinecraftScene::onImGuiRender()
{
	ImGui::Begin("Test");
	bool changed = ImGui::DragFloat3("Translation", &translation.x, 0.01f);
	changed |= ImGui::DragFloat3("Rotation", &rotation.x, 0.01f);
	changed |= ImGui::DragFloat3("Scale", &scale.x, 0.01f);
	if (changed)
		transform = glm::translate(glm::mat4(1.0f), translation) *
					glm::toMat4(glm::quat(rotation)) *
					glm::scale(glm::mat4(1.0f), scale);
	ImGui::End();
}
