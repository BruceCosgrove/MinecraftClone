#include "Models.h"

#include "Models/CubeUniformModel.h"
#include "Models/CubeTopBottomSidesModel.h"
#include "Models/CubeModel.h"
#include "Models/WaterModel.h"

std::shared_ptr<Model> Models::CUBE_UNIFORM          { new CubeUniformModel()        };
std::shared_ptr<Model> Models::CUBE_TOP_BOTTOM_SIDES { new CubeTopBottomSidesModel() };
std::shared_ptr<Model> Models::CUBE                  { new CubeModel()               };
std::shared_ptr<Model> Models::WATER                 { new WaterModel()              };
