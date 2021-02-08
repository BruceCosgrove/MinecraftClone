#pragma once

#include <memory>

#include "Minecraft/World/Models/Model.h"

class Models
{
public:
	static std::shared_ptr<Model> CUBE_UNIFORM;
	static std::shared_ptr<Model> CUBE_TOP_BOTTOM_SIDES;
	static std::shared_ptr<Model> CUBE;
	static std::shared_ptr<Model> WATER;
};
