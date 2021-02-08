#pragma once

#include "Minecraft/World/Blocks/Blocks.h"

class WaterBlock : public Block
{
public:
	WaterBlock();

	virtual bool isFaceSolid(BlockFace face, const std::shared_ptr<Block>& blockOnFace) const override { return blockOnFace == Blocks::WATER; }
	virtual void addMesh(Chunk& chunk, BasicModel& model, RenderPass renderPass, const glm::ivec3& blockPos, BlockState* blockState) const override;
};