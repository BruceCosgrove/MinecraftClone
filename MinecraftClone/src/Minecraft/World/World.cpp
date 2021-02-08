#include "World.h"

#include <time.h>

#include "Chunk.h"
#include "Generation/WorldGenerator.h"
#include "Models/RenderPass.h"

World::World()
{
	chunks = new Chunk*[chunkCount];
	for (int z = 0, i = 0; z < chunksZ; z++)
		for (int y = 0; y < chunksY; y++)
			for (int x = 0; x < chunksX; x++, i++)
				chunks[i] = new Chunk(*this, { x, y, z });

	WorldGenerator::generate(*this, time(nullptr));

	for (int i = 0; i < chunkCount; i++)
		chunks[i]->regenerateMesh();
}

World::~World()
{
	for (int i = 0; i < chunkCount; i++)
		delete chunks[i];
	delete[] chunks;
}

void World::onUpdate(float deltaTime)
{
	for (int i = 0; i < chunkCount; i++)
		chunks[i]->onUpdate(deltaTime);
}

void World::onRender()
{
	for (int i = 0; i < renderPassCount; i++)
		for (int j = 0; j < chunkCount; j++)
			chunks[j]->onRender(static_cast<RenderPass>(i));
}

BlockState* World::getBlockState(const glm::ivec3& blockPos)
{
	Chunk* chunk = getChunkFromBlockPos(blockPos);
	return chunk != nullptr ? chunk->getBlockState(getRelativeBlockPos(blockPos)) : nullptr;
}

void World::setBlockState(const glm::ivec3& blockPos, BlockState blockState)
{
	// TODO: bounds checking?
	Chunk* chunk = getChunkFromBlockPos(blockPos);
	chunk->setBlockState(getRelativeBlockPos(blockPos), blockState);
}

bool World::isBlockSolid(const glm::ivec3& blockPos, BlockFace face, const std::shared_ptr<Block>& blockOnFace)
{
	BlockState* blockState = getBlockState(blockPos);
	return blockState != nullptr && blockState->isFaceSolid(face, blockOnFace);
}

Chunk* World::getChunkFromBlockPos(const glm::ivec3& blockPos) const
{
	int chunkX = blockPos.x / Chunk::size;
	int chunkY = blockPos.y / Chunk::size;
	int chunkZ = blockPos.z / Chunk::size;

	if (blockPos.x < 0 || blockPos.x >= chunksX * Chunk::size ||
		blockPos.y < 0 || blockPos.y >= chunksY * Chunk::size ||
		blockPos.z < 0 || blockPos.z >= chunksZ * Chunk::size)
		return nullptr;

	// TODO: negative chunk positions (just add their positions to the indexing)
	// TODO: bounds checking and checking if chunk is unloaded
	return chunks[chunksX * (chunksY * chunkZ + chunkY) + chunkX];
}

glm::ivec3 World::getRelativeBlockPos(const glm::ivec3& blockPos) const
{
	return { blockPos.x % Chunk::size, blockPos.y % Chunk::size, blockPos.z % Chunk::size };
}
