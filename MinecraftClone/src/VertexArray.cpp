#include "VertexArray.h"
#include "BufferLayout.h"

#include <gl/glew.h>

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &rendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererID);
}

void VertexArray::bind() const
{
	glBindVertexArray(rendererID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::addVertexBuffer(const VertexBuffer* vertexBuffer)
{
	glBindVertexArray(rendererID);
	vertexBuffer->bind();
	vertexBuffers.push_back(vertexBuffer);
	
	const BufferLayout* layout = vertexBuffer->getBufferLayout();
	const std::vector<BufferElement>& elements = layout->getElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const BufferElement& element = elements[i];
		glEnableVertexAttribArray(i);
		// TODO: not just floats, but the ints and the bools too
		glVertexAttribPointer(i, element.count, GL_FLOAT, element.normalized, layout->getStride(), (const void*)((unsigned long long)element.offset));
	}
}
