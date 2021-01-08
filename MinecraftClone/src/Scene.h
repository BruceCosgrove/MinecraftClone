#pragma once

#include "BasicRenderer.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void onUpdate(float deltaTime) = 0;
	virtual void onRender(BasicRenderer& renderer) = 0;
	virtual void onImGuiRender() = 0;
};
