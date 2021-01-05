#pragma once

//#include <initializer_list>
#include <vector>

enum class ElementType : int
{
	// If more are added, just set them to something like this
	// Int = 0x10000001
	Float  = 0x00000001,
	Float2 = 0x00000002,
	Float3 = 0x00000003,
	Float4 = 0x00000004
};

struct BufferElement
{
	BufferElement(ElementType type, bool normalized = false)
		: type(type), normalized(normalized) {}

	ElementType type;
	bool normalized;
	int size = 0;
	int count = 0;
	int offset = 0;
};

class BufferLayout
{
public:
	BufferLayout(const std::vector<BufferElement>& elements);

	inline const std::vector<BufferElement>& getElements() const { return elements; }
	inline int getStride() const { return stride; }
private:
	std::vector<BufferElement> elements;
	int stride = 0;
};
