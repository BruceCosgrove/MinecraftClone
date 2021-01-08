#include "Renderer.h"

#include <gl/glew.h>

Renderer::Renderer()
{
	// TODO: abstract this
	// Enable depth buffer
	glEnable(GL_DEPTH);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Renderer::~Renderer()
{

}

int Renderer::getMaxTextureSlots() const
{
	int maxTextureSlots = 0;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureSlots);
	return maxTextureSlots;
}

void Renderer::onViewportResized(int width, int height) const
{
	glViewport(0, 0, width, height);
}

void Renderer::setClearColor(const glm::vec4& color) const
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::clear() const
{
	// TODO: abstract this
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, unsigned int maxIndexCount) const
{
	vertexArray.bind();
	indexBuffer.bind();
	int indexCount = maxIndexCount != 0 ? maxIndexCount : indexBuffer.getCount();

	// TODO: if unsigned shorts or chars are supported, that should be stored in IndexBuffer
	// TODO: support other primitive types, ex: GL_LINES_ADJACENCY
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}
