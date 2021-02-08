#include "Buffer.h"

#include <gl/glew.h>

BufferLayout::BufferLayout(const std::vector<BufferElement>& elements)
	: elements(elements)
{
	for (BufferElement& element : this->elements)
	{
		element.offset = stride;
		element.count = static_cast<int>(element.type) & 0x0000ffff;
		element.size = 4 * element.count;
		stride += element.size;
	}
}


static GLenum getGLUsage(BufferUsage usage)
{
	switch (usage)
	{
		case BufferUsage::StreamDraw:  return GL_STREAM_DRAW;
		case BufferUsage::StreamRead:  return GL_STREAM_READ;
		case BufferUsage::StreamCopy:  return GL_STREAM_COPY;
		case BufferUsage::StaticDraw:  return GL_STATIC_DRAW;
		case BufferUsage::StaticRead:  return GL_STATIC_READ;
		case BufferUsage::StaticCopy:  return GL_STATIC_COPY;
		case BufferUsage::DynamicDraw: return GL_DYNAMIC_DRAW;
		case BufferUsage::DynamicRead: return GL_DYNAMIC_READ;
		case BufferUsage::DynamicCopy: return GL_DYNAMIC_COPY;
		default: return 0;
	}
}

VertexBuffer::VertexBuffer(unsigned int size, const void* data, BufferUsage usage)
{
	glCreateBuffers(1, &rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, getGLUsage(usage));
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &rendererID);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(unsigned int size, const void* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}



IndexBuffer::IndexBuffer(unsigned int count, const void* data, BufferUsage usage)
	: count(count)
{
	glCreateBuffers(1, &rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, getGLUsage(usage));
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &rendererID);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::setData(unsigned int count, const void* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(unsigned int), data);
}
