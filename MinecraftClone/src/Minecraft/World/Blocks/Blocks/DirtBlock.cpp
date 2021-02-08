#include "DirtBlock.h"

#include "Minecraft/World/Models/Models.h"

DirtBlock::DirtBlock()
	: Block(1)
{

}

void DirtBlock::addMesh(Chunk& chunk, BasicModel& model, RenderPass renderPass, const glm::ivec3& blockPos, BlockState* blockState) const
{
	if (renderPass == RenderPass::OpaqueOrTransparent)
		Models::CUBE_UNIFORM->addMesh(chunk, model, blockPos, blockState, texCoords);
}
