#include "Chunk.h"

#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
//#include <iostream>

#include "Core/Application.h"
#include "Models/Model.h"

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
	BlockState* blockState = blockStates + (size * ((size_t)size * blockPos.z + blockPos.y) + blockPos.x);
	return blockState >= blockStates && blockState < (blockStates + size * size * size) ? blockState : nullptr;
}

void Chunk::regenerateMesh(const CameraController& cameraController)
{
	for (int i = 0; i < renderPassCount; i++)
	{
		BasicModel& model = models[i];
		RenderPass renderPass = static_cast<RenderPass>(i);

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
					addBlockMesh(model, renderPass, { x, y, z });

		// If the render pass is RenderPass::Translucent, then sort the triangles.
		// This will only result in artifacts with custom models (e.g. from obj files).
		if (renderPass == RenderPass::Translucent)
		{
			struct Quad
			{
				unsigned int index1;
				unsigned int index2;
				unsigned int index3;
				unsigned int index4;
				unsigned int index5;
				unsigned int index6;
				float distance; // DEBUG
			};

			// Copy indices into quads array because the quads have to be sorted
			unsigned int quadCount = model.indexCount / 6;
			Quad* quads = new Quad[quadCount];
			for (unsigned int i = 0, index = 0; i < quadCount; i++)
			{
				quads[i].index1 = model.indices[index++];
				quads[i].index2 = model.indices[index++];
				quads[i].index3 = model.indices[index++];
				quads[i].index4 = model.indices[index++];
				quads[i].index5 = model.indices[index++];
				quads[i].index6 = model.indices[index++];
			}

			std::sort(quads, quads + quadCount, [vertices = model.vertices, &cameraController](Quad& quad1, Quad& quad2)
			{
				const glm::vec3& cameraTranslation = cameraController.getTranslation();

				const glm::vec3& vertex1a = vertices[quad1.index1].position;
				const glm::vec3& vertex1b = vertices[quad1.index2].position;
				const glm::vec3& vertex1c = vertices[quad1.index3].position;
				const glm::vec3& vertex1d = vertices[quad1.index5].position;
				glm::vec3 center1 = (vertex1a + vertex1b + vertex1c + vertex1d) / 4.0f;
				quad1.distance = glm::distance(cameraTranslation, center1);

				const glm::vec3& vertex2a = vertices[quad2.index1].position;
				const glm::vec3& vertex2b = vertices[quad2.index2].position;
				const glm::vec3& vertex2c = vertices[quad2.index3].position;
				const glm::vec3& vertex2d = vertices[quad2.index5].position;
				glm::vec3 center2 = (vertex2a + vertex2b + vertex2c + vertex2d) / 4.0f;
				quad2.distance = glm::distance(cameraTranslation, center2);

				return quad2.distance < quad1.distance;
			});

			for (unsigned int i = 0, index = 0; i < quadCount; i++)
			{
				model.indices[index++] = quads[i].index1;
				model.indices[index++] = quads[i].index2;
				model.indices[index++] = quads[i].index3;
				model.indices[index++] = quads[i].index4;
				model.indices[index++] = quads[i].index5;
				model.indices[index++] = quads[i].index6;
				//std::cout << quads[i].distance << '\n';
			}

			delete[] quads;
		}
	}
}

void Chunk::addBlockMesh(BasicModel& model, RenderPass renderPass, const glm::ivec3& blockPos)
{
	BlockState* blockState = getBlockState(blockPos);
	const std::shared_ptr<Block>& block = blockState->getBlock();

	if (block->shouldRenderInPass(renderPass))
	{
		const std::shared_ptr<Model>& blockModel = block->getModel();
		if (blockModel)
			blockModel->addMesh(*this, model, blockPos, blockState, block->getTexCoords());
	}
}
