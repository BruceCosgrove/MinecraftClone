#pragma once

enum class RenderPass
{
	// Blocks that have only 0.0f and 1.0f alpha, e.g. stone, glass, saplings...
	OpaqueOrTransparent,

	// Blocks that have any alpha values, e.g. water
	Translucent
};

inline constexpr unsigned int renderPassCount = 2;
