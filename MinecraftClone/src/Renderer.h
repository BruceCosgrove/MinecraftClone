#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Material.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void setClearColor(const glm::vec4& color);
	void clear();

	void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Material& material);
};
