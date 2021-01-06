#pragma once

class IndexBuffer
{
public:
	IndexBuffer(unsigned int count, const void* data = nullptr);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	unsigned int getCount() const { return count; }
private:
	unsigned int rendererID = 0;
	unsigned int count = 0;
};
