#pragma once

#include <memory>

#include "Scene.h"
#include "OpenGLTexture.h"

class MinecraftScene : public Scene
{
public:
	MinecraftScene();
	virtual ~MinecraftScene();

	virtual void onUpdate(float deltaTime) override;
	virtual void onRender(BasicRenderer& renderer) override;
	virtual void onImGuiRender() override;
private:
	std::unique_ptr<Texture> localTexture;
	std::unique_ptr<OpenGLTexture> texture;

	glm::vec3 translation{ 0.0f };
	glm::vec3 rotation{ 0.0f };
	glm::vec3 scale{ 1.0f };
	glm::mat4 transform{ 1.0f };
};
