#pragma once

#include <glm/glm.hpp>
#include "Rendering/Basic/BasicRenderer.h"

#include "World.h"
#include "Blocks/BlockState.h"
#include "Models/RenderPass.h"

class Chunk
{
public:
	Chunk(World& world, const glm::ivec3& position = glm::ivec3(0, 0, 0));
	~Chunk();

	void onUpdate(float deltaTime);
	void onRender(RenderPass renderPass);

	BlockState* getBlockState(const glm::ivec3& blockPos);
	inline void setBlockState(const glm::ivec3& blockPos, BlockState blockState) { blockStates[size * (size * blockPos.z + blockPos.y) + blockPos.x] = blockState; }

	inline World& getWorld() { return world; }
	inline const glm::ivec3& getPosition() const { return position; }

	void regenerateMesh(const CameraController& cameraController);

	static constexpr int size = 16;
private:
	void addBlockMesh(BasicModel& model, RenderPass renderPass, const glm::ivec3& blockPos);

	World& world;
	glm::ivec3 position;
	BlockState* blockStates = nullptr;
	
	BasicModel* models;

	friend class WorldGenerator;
};
