#pragma once

#include "Blocks/BlockState.h"
#include "Minecraft/CameraController.h"

class Chunk;

class World
{
public:
	World(const CameraController& cameraController);
	~World();

	void onUpdate(float deltaTime);
	void onRender();

	BlockState* getBlockState(const glm::ivec3& blockPos);
	void setBlockState(const glm::ivec3& blockPos, BlockState blockState);

	bool isBlockSolid(const glm::ivec3& blockPos, BlockFace face, const std::shared_ptr<Block>& blockOnFace);
private:
	Chunk* getChunkFromBlockPos(const glm::ivec3& blockPos) const;
	glm::ivec3 getRelativeBlockPos(const glm::ivec3& blockPos) const;

	Chunk** chunks;
	int chunksX = 4;
	int chunksY = 4;
	int chunksZ = 4;
	int chunkCount = chunksX * chunksY * chunksZ;
	friend class WorldGenerator;
};
