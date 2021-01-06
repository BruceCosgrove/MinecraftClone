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

void Renderer::setClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::clear()
{
	// TODO: abstract this
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Material& material)
{
	vertexArray.bind();
	indexBuffer.bind();
	material.bind();

	// TODO: if unsigned shorts or chars are supported, that should be stored in IndexBuffer
	// TODO: support other primitive types, ex: GL_LINES_ADJACENCY
	// TODO: abstract this
	glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}
