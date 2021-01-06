#pragma once

class BufferLayout;

class VertexBuffer
{
public:
	VertexBuffer(unsigned int size, const void* data = nullptr);
	~VertexBuffer();

	void bind() const;
	void unbind() const;

	inline const BufferLayout* getBufferLayout() const { return layout; }
	inline void setBufferLayout(const BufferLayout* layout) { this->layout = layout; }
private:
	unsigned int rendererID = 0;
	const BufferLayout* layout = nullptr;
};
