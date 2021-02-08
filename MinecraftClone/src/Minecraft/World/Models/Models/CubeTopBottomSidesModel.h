#pragma once

#include "Minecraft/World/Models/Model.h"

class CubeTopBottomSidesModel : public Model
{
public:
	virtual void addMesh(Chunk& chunk, BasicModel& model, const glm::ivec3& blockPos, BlockState* blockState, glm::vec2** texCoords) const override;
};
