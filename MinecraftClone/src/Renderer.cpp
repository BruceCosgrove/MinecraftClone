#include "Renderer.h"

#include <gl/glew.h>

Renderer::Renderer()
{
	// Set clear color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& vertexArray)
{
	vertexArray.bind();
	glDrawElements(GL_TRIANGLES, vertexArray.getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
}
