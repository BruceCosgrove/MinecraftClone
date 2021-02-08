#pragma once

#include "Minecraft/World/Chunk.h"

class Model
{
public:
	virtual ~Model() = default;
	virtual void addMesh(Chunk& chunk, BasicModel& model, const glm::ivec3& blockPos, BlockState* blockState, glm::vec2** texCoords) const = 0;
};
