#pragma once

#include "Minecraft/World/World.h"

class WorldGenerator
{
public:
	static void generate(World& world, size_t seed = 0);
};
