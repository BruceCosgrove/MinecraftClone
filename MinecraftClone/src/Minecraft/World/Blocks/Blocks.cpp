#include "Blocks.h"

#include "Blocks/AirBlock.h"
#include "Blocks/StoneBlock.h"
#include "Blocks/BedrockBlock.h"
#include "Blocks/DirtBlock.h"
#include "Blocks/GrassBlock.h"
#include "Blocks/WaterBlock.h"

const std::shared_ptr<Block> Blocks::AIR     { new AirBlock()     };
const std::shared_ptr<Block> Blocks::STONE   { new StoneBlock()   };
const std::shared_ptr<Block> Blocks::BEDROCK { new BedrockBlock() };
const std::shared_ptr<Block> Blocks::DIRT    { new DirtBlock()    };
const std::shared_ptr<Block> Blocks::GRASS   { new GrassBlock()   };
const std::shared_ptr<Block> Blocks::WATER   { new WaterBlock()   };
