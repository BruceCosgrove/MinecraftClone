#pragma once

#include <memory>

#include "Events/Event.h"
#include "Rendering/OpenGLTexture.h"
#include "TextureAtlas.h"
#include <unordered_map>
#include "Camera.h"
#include "CameraController.h"

#include "World/World.h"

class Minecraft
{
public:
	Minecraft();
	~Minecraft();

	void onUpdate(float deltaTime);
	void onRender();
	void onImGuiRender();
	void onEvent(const Event& event);

	inline const OpenGLTexture* getTexture(int mipmapLevel = 0) const { return textureAtlases[mipmapLevel]; }
	inline const glm::ivec2& getTextureAtlasSize() const { return textureAtlasSize; }
private:
	void loadTextures();
	glm::ivec2 loadTexture(TextureAtlas& textureAtlas, const std::string& filePath);
	void unloadTextures();
	Texture** localTextureAtlases = nullptr;
	OpenGLTexture** textureAtlases = nullptr;
	int textureAtlasCount = 1;
	glm::ivec2 textureAtlasSize{ 0 };
	
	Camera camera;
	CameraController cameraController;

	World* world;
};
