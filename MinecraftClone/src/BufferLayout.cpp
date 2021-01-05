#include "BufferLayout.h"

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
