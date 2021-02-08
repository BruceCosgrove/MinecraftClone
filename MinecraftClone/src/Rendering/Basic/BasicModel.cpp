#include "BasicModel.h"

BasicModel::~BasicModel()
{
	delete[] vertices;
	delete[] indices;
}
