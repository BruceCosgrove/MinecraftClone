#pragma once

#include "BasicVertex.h"

struct BasicModel
{
	~BasicModel();

	BasicVertex* vertices = nullptr;
	unsigned int vertexCount = 0;
	unsigned int* indices = nullptr;
	unsigned int indexCount = 0;
};
