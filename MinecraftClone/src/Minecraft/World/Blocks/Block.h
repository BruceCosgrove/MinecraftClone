#pragma once

#include <memory>

#include "BlockFace.h"
#include "Minecraft/World/Models/RenderPass.h"
#include "Rendering/Basic/BasicModel.h"

typedef unsigned int BlockID;

class World;
class Chunk;
class BlockState;
class Model;

class Block
{
public:
	Block(int textureCount = 0, std::shared_ptr<Model> model = nullptr);
	virtual ~Block();

	inline BlockID getID() const { return id; }
	inline const std::shared_ptr<Model>& getModel() const { return model; }
	inline glm::vec2** getTexCoords() const { return texCoords; }

	virtual bool isFaceSolid(BlockFace face, const std::shared_ptr<Block>& blockOnFace) const { return true; }
	virtual bool shouldRenderInPass(RenderPass renderPass) const { return renderPass == RenderPass::OpaqueOrTransparent; }

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
	int textureCount;

	std::shared_ptr<Model> model;
};
