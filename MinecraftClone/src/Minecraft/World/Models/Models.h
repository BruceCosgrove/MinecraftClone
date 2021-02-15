#pragma once

#include <memory>

#include "Minecraft/World/Models/Model.h"

class Models
{
public:
	static const std::shared_ptr<Model> CUBE_UNIFORM;
	static const std::shared_ptr<Model> CUBE_TOP_BOTTOM_SIDES;
	static const std::shared_ptr<Model> CUBE;
	static const std::shared_ptr<Model> WATER;
private:
	static void init();
	friend class Minecraft;
};
