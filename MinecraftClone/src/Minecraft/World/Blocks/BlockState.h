#pragma once

#include "Blocks.h"

class BlockState
{
public:
	BlockState(std::shared_ptr<Block> block = Blocks::AIR);

	inline const std::shared_ptr<Block>& getBlock() const { return block; }
	inline bool isFaceSolid(BlockFace face, const std::shared_ptr<Block>& blockOnFace) const { return block->isFaceSolid(face, blockOnFace); }
private:
	std::shared_ptr<Block> block;
};
