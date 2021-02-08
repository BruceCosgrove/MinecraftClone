#include "WaterModel.h"

void WaterModel::addMesh(Chunk& chunk, BasicModel& model, const glm::ivec3& blockPos, BlockState* blockState, glm::vec2** texCoords) const
{
	int offset = model.vertexCount;
	int facesAdded = 0;

	// Left
	BlockState* leftBlockState = chunk.getWorld().getBlockState((glm::ivec3(-1, 0, 0) += blockPos) += chunk.getPosition() * Chunk::size);
	if (leftBlockState == nullptr || (leftBlockState->getBlock() != blockState->getBlock() && !leftBlockState->isFaceSolid(BlockFace::Right, blockState->getBlock())))
	{
		model.vertices[model.vertexCount++] = { { blockPos.x + 0.0f, blockPos.y + 0.0f, blockPos.z + 0.0f }, texCoords[0][0], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 0.0f, blockPos.y + 0.0f, blockPos.z + 1.0f }, texCoords[0][1], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 0.0f, blockPos.y + 1.0f, blockPos.z + 1.0f }, texCoords[0][2], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 0.0f, blockPos.y + 1.0f, blockPos.z + 0.0f }, texCoords[0][3], { 1.0f, 1.0f, 1.0f, 1.0f } };
		facesAdded++;
	}

	// Right
	BlockState* rightBlockState = chunk.getWorld().getBlockState((glm::ivec3(1, 0, 0) += blockPos) += chunk.getPosition() * Chunk::size);
	if (rightBlockState == nullptr || (rightBlockState->getBlock() != blockState->getBlock() && !rightBlockState->isFaceSolid(BlockFace::Left, blockState->getBlock())))
	{
		model.vertices[model.vertexCount++] = { { blockPos.x + 1.0f, blockPos.y + 0.0f, blockPos.z + 1.0f }, texCoords[0][0], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 1.0f, blockPos.y + 0.0f, blockPos.z + 0.0f }, texCoords[0][1], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 1.0f, blockPos.y + 1.0f, blockPos.z + 0.0f }, texCoords[0][2], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 1.0f, blockPos.y + 1.0f, blockPos.z + 1.0f }, texCoords[0][3], { 1.0f, 1.0f, 1.0f, 1.0f } };
		facesAdded++;
	}

	// Bottom
	BlockState* bottomBlockState = chunk.getWorld().getBlockState((glm::ivec3(0, -1, 0) += blockPos) += chunk.getPosition() * Chunk::size);
	if (bottomBlockState == nullptr || (bottomBlockState->getBlock() != blockState->getBlock() && !bottomBlockState->isFaceSolid(BlockFace::Top, blockState->getBlock())))
	{
		model.vertices[model.vertexCount++] = { { blockPos.x + 0.0f, blockPos.y + 0.0f, blockPos.z + 0.0f }, texCoords[0][0], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 1.0f, blockPos.y + 0.0f, blockPos.z + 0.0f }, texCoords[0][1], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 1.0f, blockPos.y + 0.0f, blockPos.z + 1.0f }, texCoords[0][2], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 0.0f, blockPos.y + 0.0f, blockPos.z + 1.0f }, texCoords[0][3], { 1.0f, 1.0f, 1.0f, 1.0f } };
		facesAdded++;
	}

	// Top
	BlockState* topBlockState = chunk.getWorld().getBlockState((glm::ivec3(0, 1, 0) += blockPos) += chunk.getPosition() * Chunk::size);
	if (topBlockState == nullptr || (topBlockState->getBlock() != blockState->getBlock() && !topBlockState->isFaceSolid(BlockFace::Bottom, blockState->getBlock())))
	{
		model.vertices[model.vertexCount++] = { { blockPos.x + 0.0f, blockPos.y + 1.0f, blockPos.z + 1.0f }, texCoords[0][0], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 1.0f, blockPos.y + 1.0f, blockPos.z + 1.0f }, texCoords[0][1], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 1.0f, blockPos.y + 1.0f, blockPos.z + 0.0f }, texCoords[0][2], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 0.0f, blockPos.y + 1.0f, blockPos.z + 0.0f }, texCoords[0][3], { 1.0f, 1.0f, 1.0f, 1.0f } };
		facesAdded++;
	}

	// Back
	BlockState* backBlockState = chunk.getWorld().getBlockState((glm::ivec3(0, 0, -1) += blockPos) += chunk.getPosition() * Chunk::size);
	if (backBlockState == nullptr || (backBlockState->getBlock() != blockState->getBlock() && !backBlockState->isFaceSolid(BlockFace::Front, blockState->getBlock())))
	{
		model.vertices[model.vertexCount++] = { { blockPos.x + 1.0f, blockPos.y + 0.0f, blockPos.z + 0.0f }, texCoords[0][0], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 0.0f, blockPos.y + 0.0f, blockPos.z + 0.0f }, texCoords[0][1], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 0.0f, blockPos.y + 1.0f, blockPos.z + 0.0f }, texCoords[0][2], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 1.0f, blockPos.y + 1.0f, blockPos.z + 0.0f }, texCoords[0][3], { 1.0f, 1.0f, 1.0f, 1.0f } };
		facesAdded++;
	}

	// Front
	BlockState* frontBlockState = chunk.getWorld().getBlockState((glm::ivec3(0, 0, 1) += blockPos) += chunk.getPosition() * Chunk::size);
	if (frontBlockState == nullptr || (frontBlockState->getBlock() != blockState->getBlock() && !frontBlockState->isFaceSolid(BlockFace::Bottom, blockState->getBlock())))
	{
		model.vertices[model.vertexCount++] = { { blockPos.x + 0.0f, blockPos.y + 0.0f, blockPos.z + 1.0f }, texCoords[0][0], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 1.0f, blockPos.y + 0.0f, blockPos.z + 1.0f }, texCoords[0][1], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 1.0f, blockPos.y + 1.0f, blockPos.z + 1.0f }, texCoords[0][2], { 1.0f, 1.0f, 1.0f, 1.0f } };
		model.vertices[model.vertexCount++] = { { blockPos.x + 0.0f, blockPos.y + 1.0f, blockPos.z + 1.0f }, texCoords[0][3], { 1.0f, 1.0f, 1.0f, 1.0f } };
		facesAdded++;
	}

	for (int i = 0; i < facesAdded; i++, offset += 4)
	{
		model.indices[model.indexCount++] = offset + 0;
		model.indices[model.indexCount++] = offset + 1;
		model.indices[model.indexCount++] = offset + 2;
		model.indices[model.indexCount++] = offset + 2;
		model.indices[model.indexCount++] = offset + 3;
		model.indices[model.indexCount++] = offset + 0;
	}
}
