#include "Chunk.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Core/Application.h"

Chunk::Chunk(World& world, const glm::ivec3& position)
	: world(world), position(position)
{
	blockStates = new BlockState[size * size * size];
	models = new BasicModel[renderPassCount];
}

Chunk::~Chunk()
{
	delete[] models;

	// TODO: save to disc
	delete[] blockStates;
}

void Chunk::onUpdate(float deltaTime)
{
	
}

void Chunk::onRender(RenderPass renderPass)
{
	BasicRenderer::submit(models[static_cast<size_t>(renderPass)], glm::translate(glm::mat4(1.0f), glm::vec3(position * size)), Application::get().getMinecraft().getTexture());
}

BlockState* Chunk::getBlockState(const glm::ivec3& blockPos)
{
	BlockState* blockState = blockStates + (size * (size * blockPos.z + blockPos.y) + blockPos.x);
	return blockState >= blockStates && blockState < (blockStates + size * size * size) ? blockState : nullptr;
}

void Chunk::regenerateMesh()
{
	for (int i = 0; i < renderPassCount; i++)
	{
		BasicModel& model = models[i];

		delete[] model.vertices;
		delete[] model.indices;

		// TODO: calculate how many vertices and indices there should be
		model.vertexCount = 0;
		model.indexCount = 0;
		model.vertices = new BasicVertex[4 * 6 * size * size * size / 8]; // Max of 24 per block (blocks in a 3D checkerboard pattern)
		model.indices = new unsigned int[6 * 6 * size * size * size / 8]; // Max of 36 per block (blocks in a 3D checkerboard pattern)

		for (int z = 0; z < size; z++)
			for (int y = 0; y < size; y++)
				for (int x = 0; x < size; x++)
					addBlockMesh(model, static_cast<RenderPass>(i), { x, y, z });
	}
}

void Chunk::addBlockMesh(BasicModel& model, RenderPass renderPass, const glm::ivec3& blockPos)
{
	glm::ivec3 blockPosition = position * size + blockPos;
	BlockState* blockState = world.getBlockState(blockPosition);
	const std::shared_ptr<Block>& block = blockState->getBlock();

	block->addMesh(*this, model, renderPass, blockPos, blockState);
}
