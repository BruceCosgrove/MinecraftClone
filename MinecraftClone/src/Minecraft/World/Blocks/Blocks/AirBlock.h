#pragma once

#include "Minecraft/World/Blocks/Block.h"

class AirBlock : public Block
{
public:
	virtual bool isFaceSolid(BlockFace face, const std::shared_ptr<Block>& block) const override { return false; }
};
