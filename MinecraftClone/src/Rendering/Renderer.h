#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"
#include "Buffer.h"

class Renderer
{
private:
	static void init();
	static void shutdown();
	friend class Application;
public:
	// Query commands
	// TODO: these belong in an opengl context class
	static int getMaxTextureSlots();
	static int getMaxTextureSize();

	// Event-based commands
	static void onViewportResized(int width, int height);

	// General commands
	static void setClearColor(const glm::vec4& color);
	static void clear();

	// Enable/disable commands
	static void enableDepthTest(bool enable = true);
	static void enableDepthMask(bool enable = true);
	static void enableCullFace(bool enable = true);
	static void enableBlending(bool enable = true);
	
	// Rendering commands
	static void drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, unsigned int maxIndexCount = 0);
};
