#pragma once

#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	void addVertexBuffer(const VertexBuffer* vertexBuffer);
	void setIndexBuffer(const IndexBuffer* indexBuffer);

	const std::vector<const VertexBuffer*>& getVertexBuffers() { return vertexBuffers; }
	const IndexBuffer* getIndexBuffer() const { return indexBuffer; }
private:
	unsigned int rendererID;
	std::vector<const VertexBuffer*> vertexBuffers;
	const IndexBuffer* indexBuffer = nullptr;
};
