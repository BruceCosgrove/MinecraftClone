#include "WaterBlock.h"

#include "Minecraft/World/Models/Models.h"

WaterBlock::WaterBlock()
	: Block(1)
{

}

void WaterBlock::addMesh(Chunk& chunk, BasicModel& model, RenderPass renderPass, const glm::ivec3& blockPos, BlockState* blockState) const
{
	if (renderPass == RenderPass::Translucent)
		Models::WATER->addMesh(chunk, model, blockPos, blockState, texCoords);
}
