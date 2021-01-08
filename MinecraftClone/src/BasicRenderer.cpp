#include "BasicRenderer.h"

#include <vector>

#include "FileIO.h"

BasicRenderer::BasicRenderer()
{
	// Setup texture slots
	maxTextures = (unsigned int)renderer.getMaxTextureSlots();
	localTextures = new const OpenGLTexture*[maxTextures];

	// Setup local buffers
	// these are only ~3.8MB each, can be increased dramatically
	maxVertices = 100000; // TODO: query drivers
	maxIndices = 100000; // TODO: query drivers
	localVertexBufferStart = new BasicVertex[maxVertices];
	localVertexBufferCurrent = localVertexBufferStart;
	localIndexBufferStart = new unsigned int[maxIndices];
	localIndexBufferCurrent = localIndexBufferStart;

	// Setup internal buffers
	vertexBuffer.reset(new VertexBuffer(maxVertices * sizeof(BasicVertex), nullptr, BufferUsage::DynamicDraw));
	vertexBuffer->setLayout({{
		{ ElementType::Float3 },
		{ ElementType::Float4 },
		{ ElementType::Float2 },
		{ ElementType::Float  }
	}});

	vertexArray.reset(new VertexArray());
	vertexArray->addVertexBuffer(vertexBuffer.get());

	indexBuffer.reset(new IndexBuffer(maxIndices, nullptr, BufferUsage::DynamicDraw));

	// Setup shader
	int* samplers = new int[maxTextures];
	for (unsigned int i = 0; i < maxTextures; i++)
		samplers[i] = i;

	std::vector<ShaderFile> shaderFiles = {
		{ ShaderType::Vertex, FileIO::readFile("resources/shaders/Basic_vertex.glsl") },
		{ ShaderType::Fragment, FileIO::readFile("resources/shaders/Basic_fragment.glsl") }
	};
	shader.reset(new ShaderProgram(shaderFiles));
	shader->bind();
	shader->setUniforms("textures", samplers, maxTextures);

	delete[] samplers;
}

BasicRenderer::~BasicRenderer()
{
	delete[] localVertexBufferStart;
	delete[] localIndexBufferStart;
	delete[] localTextures;
}

void BasicRenderer::beginScene(const glm::mat4& cameraTransform, const glm::mat4& projection)
{
	// Set shader uniforms
	shader->bind();
	shader->setUniform("projection", projection);
	shader->setUniform("cameraTransform", cameraTransform);

	reset();
}

void BasicRenderer::endScene()
{
	// Copy local buffers to internal buffers
	unsigned int vertexBufferSize = (unsigned int)(localVertexCount * sizeof(BasicVertex));
	vertexBuffer->setData(vertexBufferSize, localVertexBufferStart);
	
	unsigned int indexBufferSize = (unsigned int)(localIndexCount * sizeof(unsigned int));
	indexBuffer->setData(indexBufferSize, localIndexBufferStart);

	// Bind textures
	for (unsigned int i = 0; i < textureCount; i++)
		localTextures[i]->bind(i);

	// Actually render
	renderer.drawIndexed(*vertexArray, *indexBuffer, localIndexCount);
	reset();
}

bool BasicRenderer::ensureBatch(unsigned int vertexCount, unsigned int indexCount, unsigned int texIndex)
{
	if (localVertexCount + vertexCount >= maxVertices ||
		localIndexCount + indexCount >= maxIndices ||
		texIndex >= maxTextures)
	{
		endScene();
		return true;
	}
	return false;
}

void BasicRenderer::reset()
{
	// Reset local buffers
	localVertexCount = 0;
	localVertexBufferCurrent = localVertexBufferStart;

	localIndexCount = 0;
	localIndexBufferCurrent = localIndexBufferStart;

	textureCount = 0;
}

unsigned int BasicRenderer::getTextureIndex(const OpenGLTexture* texture)
{
	if (texture == nullptr)
		return 0;

	for (unsigned int i = 0; i < textureCount; i++)
		if (*(texture->getTexture()) == *(localTextures[i]->getTexture()))
			return i;

	return textureCount;
}

void BasicRenderer::submit(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount, const unsigned int* indices, const glm::mat4& transform, const OpenGLTexture* texture)
{
	// Handle textures
	unsigned int texIndex = getTextureIndex(texture);
	if (ensureBatch(vertexCount, indexCount, texIndex))
		texIndex = 0;
	if (texIndex == textureCount)
	{
		localTextures[texIndex] = texture;
		textureCount++;
	}

	// Handle vertices
	for (unsigned int i = 0; i < vertexCount; i++, localVertexBufferCurrent++)
	{
		localVertexBufferCurrent->position = transform * glm::vec4(vertices[i].position, 1.0f);
		localVertexBufferCurrent->texCoord = vertices[i].texCoord;
		localVertexBufferCurrent->tintColor = vertices[i].tintColor;
		localVertexBufferCurrent->texIndex = (float)texIndex;
	}

	// Handle indices
	for (unsigned int i = 0; i < indexCount; i++, localIndexBufferCurrent++)
		*localIndexBufferCurrent = localVertexCount + indices[i];

	localVertexCount += vertexCount;
	localIndexCount += indexCount;
}
