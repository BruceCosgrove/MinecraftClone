#pragma once

#include <memory>

#include "Block.h"

class Blocks
{
public:
	static const std::shared_ptr<Block> AIR;
	static const std::shared_ptr<Block> STONE;
	static const std::shared_ptr<Block> BEDROCK;
	static const std::shared_ptr<Block> DIRT;
	static const std::shared_ptr<Block> GRASS;
	static const std::shared_ptr<Block> WATER;
private:
	static void init();
	friend class Minecraft;
};
