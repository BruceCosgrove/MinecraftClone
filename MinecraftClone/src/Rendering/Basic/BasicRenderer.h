#pragma once

#include <memory>

#include "Rendering/Shader.h"
#include "Rendering/OpenGLTexture.h"
#include "Rendering/Renderer.h"
#include "BasicVertex.h"
#include "BasicModel.h"

class BasicRenderer
{
private:
	static void init();
	static void shutdown();
	friend class Renderer;
public:
	static void beginScene(const glm::mat4& cameraTransform, const glm::mat4& projection);
	static void endScene();

	static void submit(const BasicModel& model, const glm::mat4& transform = glm::mat4(1.0f), const OpenGLTexture* texture = nullptr);
private:
	static bool ensureBatch(unsigned int vertexCount, unsigned int indexCount, unsigned int texIndex = 0);
	static void reset();
	static unsigned int getTextureIndex(const OpenGLTexture* texture);
};
