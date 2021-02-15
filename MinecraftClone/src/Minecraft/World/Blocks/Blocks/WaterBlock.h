#pragma once

#include "Minecraft/World/Blocks/Blocks.h"

class WaterBlock : public Block
{
public:
	WaterBlock();

	virtual bool shouldRenderInPass(RenderPass renderPass) const override { return renderPass == RenderPass::Translucent; }
	virtual bool isFaceSolid(BlockFace face, const std::shared_ptr<Block>& blockOnFace) const override { return blockOnFace == Blocks::WATER; }
};