#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"
#include "Buffer.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	// Query commands
	// TODO: these belong in an opengl context class
	int getMaxTextureSlots() const;

	// Event-based commands
	void onViewportResized(int width, int height) const;

	// General commands
	void setClearColor(const glm::vec4& color) const;
	void clear() const;
	
	// Rendering commands
	void drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, unsigned int maxIndexCount = 0) const;
};
