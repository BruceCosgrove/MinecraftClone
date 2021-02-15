#include "Blocks.h"

#include "Blocks/AirBlock.h"
#include "Blocks/StoneBlock.h"
#include "Blocks/BedrockBlock.h"
#include "Blocks/DirtBlock.h"
#include "Blocks/GrassBlock.h"
#include "Blocks/WaterBlock.h"

const std::shared_ptr<Block> Blocks::AIR = nullptr;
const std::shared_ptr<Block> Blocks::STONE = nullptr;
const std::shared_ptr<Block> Blocks::BEDROCK = nullptr;
const std::shared_ptr<Block> Blocks::DIRT = nullptr;
const std::shared_ptr<Block> Blocks::GRASS = nullptr;
const std::shared_ptr<Block> Blocks::WATER = nullptr;

// This is to make the blocks immutable, but so I can make sure they will be registered AFTER block models
#define INIT(block, type) (*(std::shared_ptr<Block>*)&(block)).reset(new type())

void Blocks::init()
{
	INIT(AIR, AirBlock);
	INIT(STONE, StoneBlock);
	INIT(BEDROCK, BedrockBlock);
	INIT(DIRT, DirtBlock);
	INIT(GRASS, GrassBlock);
	INIT(WATER, WaterBlock);
}
