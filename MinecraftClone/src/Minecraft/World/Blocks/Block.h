#pragma once

#include <memory>

#include "BlockFace.h"
#include "Minecraft/World/Models/RenderPass.h"
#include "Rendering/Basic/BasicModel.h"

typedef unsigned int BlockID;

class World;
class Chunk;
class BlockState;

class Block
{
public:
	Block(int textureCount = 0);
	virtual ~Block();

	BlockID getID() const { return id; }
	virtual bool isFaceSolid(BlockFace face, const std::shared_ptr<Block>& blockOnFace) const { return true; }

	virtual void addMesh(Chunk& chunk, BasicModel& model, RenderPass renderPass, const glm::ivec3& blockPos, BlockState* blockState) const {}

	struct TextureData
	{
		glm::ivec2 position;
		glm::ivec2 size;
	};
	void setTexCoords(const glm::ivec2& textureAtlasSize, const TextureData* textures);
protected:
	static BlockID nextID;
	BlockID id;

	glm::vec2** texCoords;
	glm::vec2* textureSizes;
	int textureCount;
};
