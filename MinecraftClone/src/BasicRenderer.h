#pragma once

#include <memory>

#include "Shader.h"
#include "OpenGLTexture.h"
#include "Renderer.h"

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec4 tintColor;
};

class BasicRenderer
{
public:
	BasicRenderer();
	~BasicRenderer();

	inline Renderer& getRenderer() { return renderer; }

	// TODO: camera
	void beginScene(const glm::mat4& cameraTransform, const glm::mat4& projection);
	void endScene();

	void submit(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount, const unsigned int* indices, const glm::mat4& transform = glm::mat4(1.0f), const OpenGLTexture* texture = nullptr);
private:
	struct BasicVertex
	{
		glm::vec3 position;
		glm::vec4 tintColor;
		glm::vec2 texCoord;
		float texIndex;
	};

	bool ensureBatch(unsigned int vertexCount, unsigned int indexCount, unsigned int texIndex = 0);
	void reset();
	unsigned int getTextureIndex(const OpenGLTexture* texture);

	// TODO: singleton?
	Renderer renderer;

	std::unique_ptr<ShaderProgram> shader;
	std::unique_ptr<VertexArray> vertexArray;
	std::unique_ptr<VertexBuffer> vertexBuffer;
	std::unique_ptr<IndexBuffer> indexBuffer;

	unsigned int localIndexCount = 0;
	unsigned int* localIndexBufferStart = nullptr;
	unsigned int* localIndexBufferCurrent = nullptr;
	unsigned int localVertexCount = 0;
	BasicVertex* localVertexBufferStart = nullptr;
	BasicVertex* localVertexBufferCurrent = nullptr;

	const OpenGLTexture** localTextures;
	unsigned int textureCount = 0;

	unsigned int maxVertices;
	unsigned int maxIndices;
	unsigned int maxTextures;
};
