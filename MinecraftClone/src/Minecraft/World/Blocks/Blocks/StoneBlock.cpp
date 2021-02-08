#include "StoneBlock.h"

#include "Minecraft/World/Models/Models.h"

StoneBlock::StoneBlock()
	: Block(1)
{

}

void StoneBlock::addMesh(Chunk& chunk, BasicModel& model, RenderPass renderPass, const glm::ivec3& blockPos, BlockState* blockState) const
{
	// TODO: have blocks retain a reference to their model
	if (renderPass == RenderPass::OpaqueOrTransparent)
		Models::CUBE_UNIFORM->addMesh(chunk, model, blockPos, blockState, texCoords);
}
