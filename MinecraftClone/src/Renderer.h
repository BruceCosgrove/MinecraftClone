#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void setClearColor(const glm::vec4& color);
	void clear();

	void draw(const VertexArray& vertexArray);
};
