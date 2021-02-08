#include "BedrockBlock.h"

#include "Minecraft/World/Models/Models.h"

BedrockBlock::BedrockBlock()
	: Block(1)
{

}

void BedrockBlock::addMesh(Chunk& chunk, BasicModel& model, RenderPass renderPass, const glm::ivec3& blockPos, BlockState* blockState) const
{
	if (renderPass == RenderPass::OpaqueOrTransparent)
		Models::CUBE_UNIFORM->addMesh(chunk, model, blockPos, blockState, texCoords);
}
