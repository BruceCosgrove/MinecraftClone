#pragma once

#include <vector>

#include "Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	void addVertexBuffer(const VertexBuffer* vertexBuffer);
	inline const std::vector<const VertexBuffer*>& getVertexBuffers() { return vertexBuffers; }
private:
	unsigned int rendererID = 0;
	std::vector<const VertexBuffer*> vertexBuffers;
};
