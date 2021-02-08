#include "GrassBlock.h"

#include "Minecraft/World/Models/Models.h"

GrassBlock::GrassBlock()
	: Block(3)
{

}

void GrassBlock::addMesh(Chunk& chunk, BasicModel& model, RenderPass renderPass, const glm::ivec3& blockPos, BlockState* blockState) const
{
	if (renderPass == RenderPass::OpaqueOrTransparent)
		Models::CUBE_TOP_BOTTOM_SIDES->addMesh(chunk, model, blockPos, blockState, texCoords);
}
