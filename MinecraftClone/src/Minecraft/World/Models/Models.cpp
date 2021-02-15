#include "Models.h"

#include "Models/CubeUniformModel.h"
#include "Models/CubeTopBottomSidesModel.h"
#include "Models/CubeModel.h"
#include "Models/WaterModel.h"

const std::shared_ptr<Model> Models::CUBE_UNIFORM = nullptr;
const std::shared_ptr<Model> Models::CUBE_TOP_BOTTOM_SIDES = nullptr;
const std::shared_ptr<Model> Models::CUBE = nullptr;
const std::shared_ptr<Model> Models::WATER = nullptr;

#define INIT(blockModel, type) (*(std::shared_ptr<Model>*)&(blockModel)).reset(new type())

void Models::init()
{
	INIT(CUBE_UNIFORM, CubeUniformModel);
	INIT(CUBE_TOP_BOTTOM_SIDES, CubeTopBottomSidesModel);
	INIT(CUBE, CubeModel);
	INIT(WATER, WaterModel);
}
