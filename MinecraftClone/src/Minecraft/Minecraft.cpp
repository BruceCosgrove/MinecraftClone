#include "Minecraft.h"

#include "Rendering/Basic/BasicRenderer.h"
#include "Events/WindowEvents.h"
#include "Core/Application.h"

Minecraft::Minecraft()
	: camera(glm::radians(90.0f), 0.01f, 1000.0f)
{
	cameraController.setTranslation({ 32, 48, 32 });

	Window& window = Application::get().getWindow();
	camera.onViewportResize(window.getWidth(), window.getHeight());

	loadTextures();

	// TODO: since chunks won't be created in the menu screen, this doesn't necessarily have to be manually called
	// However, all chunks whose meshes should be regenerated should do so in the same update or spread out over updates
	world = new World();
}

Minecraft::~Minecraft()
{
	delete world;
	unloadTextures();
}

void Minecraft::onUpdate(float deltaTime)
{
	// TODO: camera controller should be attached to a player entity
	// entities should be owned by the world, so this would eventually be called somewhere in world->onUpdate(deltaTime)
	cameraController.onUpdate(deltaTime);

	world->onUpdate(deltaTime);
}

void Minecraft::onRender()
{
	Renderer::clear();
	Renderer::setClearColor({ 0.124590f, 0.662745f, 1.0f, 1.0f });

	BasicRenderer::beginScene(cameraController.getTransform(), camera.getProjection());
	world->onRender();
	BasicRenderer::endScene();
}

void Minecraft::onImGuiRender()
{
	
}

void Minecraft::onEvent(const Event& event)
{
	cameraController.onEvent(event);

	switch (event.getType())
	{
		case EventType::WindowResize:
		{
			const WindowResizeEvent& wre = (const WindowResizeEvent&)event;
			camera.onViewportResize(wre.getWidth(), wre.getHeight());
			break;
		}
	}
}

void Minecraft::loadTextures()
{
	TextureAtlas textureAtlas;

	loadTexture(textureAtlas, "./resources/textures/missing.png");
	glm::ivec2 bedrockTexCoord = loadTexture(textureAtlas, "./resources/textures/bedrock.png");
	loadTexture(textureAtlas, "./resources/textures/coal_ore.png");
	loadTexture(textureAtlas, "./resources/textures/cobblestone.png");
	loadTexture(textureAtlas, "./resources/textures/crafting_table_front.png");
	loadTexture(textureAtlas, "./resources/textures/crafting_table_side.png");
	loadTexture(textureAtlas, "./resources/textures/crafting_table_top.png");
	glm::ivec2 dirtTexCoord = loadTexture(textureAtlas, "./resources/textures/dirt.png");
	glm::ivec2 grassSideTexCoord = loadTexture(textureAtlas, "./resources/textures/grass_side.png");
	glm::ivec2 grassTopTexCoord = loadTexture(textureAtlas, "./resources/textures/grass_top.png");
	loadTexture(textureAtlas, "./resources/textures/gravel.png");
	loadTexture(textureAtlas, "./resources/textures/log_oak.png");
	loadTexture(textureAtlas, "./resources/textures/log_oak_top.png");
	loadTexture(textureAtlas, "./resources/textures/planks_oak.png");
	loadTexture(textureAtlas, "./resources/textures/sand.png");
	loadTexture(textureAtlas, "./resources/textures/sapling_oak.png");
	glm::ivec2 stoneTexCoord = loadTexture(textureAtlas, "./resources/textures/stone.png");
	glm::ivec2 waterTexCoord = loadTexture(textureAtlas, "./resources/textures/water.png");

	constexpr glm::ivec2 textureSize{ 16 };

	// TODO: Block models: some preset ones like cube-all
	const Block::TextureData stoneTexCoords[]{ { stoneTexCoord, textureSize } };
	Blocks::STONE->setTexCoords(textureAtlas.getTextureSize(), stoneTexCoords);
	const Block::TextureData bedrockTexCoords[]{ { bedrockTexCoord, textureSize } };
	Blocks::BEDROCK->setTexCoords(textureAtlas.getTextureSize(), bedrockTexCoords);
	const Block::TextureData dirtTexCoords[]{ { dirtTexCoord, textureSize } };
	Blocks::DIRT->setTexCoords(textureAtlas.getTextureSize(), dirtTexCoords);
	const Block::TextureData grassTexCoords[]{ { grassTopTexCoord, textureSize }, { dirtTexCoord, textureSize }, { grassSideTexCoord, textureSize } };
	Blocks::GRASS->setTexCoords(textureAtlas.getTextureSize(), grassTexCoords);
	const Block::TextureData waterTexCoords[]{ { waterTexCoord, textureSize } };
	Blocks::WATER->setTexCoords(textureAtlas.getTextureSize(), waterTexCoords);

	// TODO: not necessary to keep the local copy
	textureAtlasSize = textureAtlas.getTextureSize();
	localTextureAtlases = textureAtlas.create(textureAtlasCount);
	textureAtlases = new OpenGLTexture*[textureAtlasCount];
	for (int i = 0; i < textureAtlasCount; i++)
		textureAtlases[i] = new OpenGLTexture(localTextureAtlases[i]);
}

glm::ivec2 Minecraft::loadTexture(TextureAtlas& textureAtlas, const std::string& filePath)
{
	std::shared_ptr<Texture> texture(new Texture(filePath, 4));
	return textureAtlas.addTexture(texture);
}

void Minecraft::unloadTextures()
{
	for (int i = 0; i < textureAtlasCount; i++)
	{
		delete textureAtlases[i];
		delete localTextureAtlases[i];
	}
	delete[] textureAtlases;
	delete[] localTextureAtlases;
}
