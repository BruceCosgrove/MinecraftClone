#include "Block.h"

BlockID Block::nextID = 0;

Block::Block(int textureCount, std::shared_ptr<Model> model)
	: id(nextID++), textureCount(textureCount), model(model)
{
	texCoords = new glm::vec2*[textureCount];
	for (int i = 0; i < textureCount; i++)
		texCoords[i] = new glm::vec2[4];
}

Block::~Block()
{
	for (int i = 0; i < textureCount; i++)
		delete[] texCoords[i];
	delete[] texCoords;
}

void Block::setTexCoords(const glm::ivec2& textureAtlasSize, const TextureData* textures)
{
	for (int i = 0; i < textureCount; i++)
	{
		glm::vec2 start = glm::vec2(textures[i].position) /= textureAtlasSize;
		glm::vec2 end = (glm::vec2(textures[i].size) /= textureAtlasSize) += start;

		texCoords[i][0] = { start.x, end.y   };
		texCoords[i][1] = { end.x,   end.y   };
		texCoords[i][2] = { end.x,   start.y };
		texCoords[i][3] = { start.x, start.y };
	}
}
