#include "WorldGenerator.h"
#include "Minecraft/World/Chunk.h"

#include <siv/PerlinNoise.hpp>
#include <iostream>

void WorldGenerator::generate(World& world, size_t seed)
{
	std::cout << "World Seed: " << seed << '\n';
	siv::BasicPerlinNoise<float> noise((uint32_t)seed);

	int maxZ = Chunk::size * world.chunksZ;
	int maxX = Chunk::size * world.chunksX;

	for (int z = 0; z < maxZ; z++)
	{
		for (int x = 0; x < maxX; x++)
		{
			int defaultHeight = 32;
			int grassHeight = (int)(defaultHeight + 7.0f * noise.noise2D(x / 20.0f, z / 20.0f));
			int dirtHeight = grassHeight - 1;
			int stoneHeight = dirtHeight - 3;

			world.setBlockState({ x, 0, z }, BlockState(Blocks::BEDROCK));
			for (int y = 1; y <= stoneHeight; y++)
				world.setBlockState({ x, y, z }, BlockState(Blocks::STONE));
			for (int y = stoneHeight; y <= dirtHeight; y++)
				world.setBlockState({ x, y, z }, BlockState(Blocks::DIRT));
			world.setBlockState({ x, grassHeight, z }, BlockState(Blocks::GRASS));
			for (int y = grassHeight + 1; y <= defaultHeight; y++)
				world.setBlockState({ x, y, z }, BlockState(Blocks::WATER));
		}
	}
}
