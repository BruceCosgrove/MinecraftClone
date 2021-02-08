#include "Block.h"

BlockID Block::nextID = 0;

Block::Block(int textureCount)
	: id(nextID++), textureCount(textureCount)
{
	texCoords = new glm::vec2*[textureCount];
	for (int i = 0; i < textureCount; i++)
		texCoords[i] = new glm::vec2[4];
	textureSizes = new glm::vec2[textureCount];
}

Block::~Block()
{
	for (int i = 0; i < textureCount; i++)
		delete[] texCoords[i];
	delete[] texCoords;
	delete[] textureSizes;
}

void Block::setTexCoords(const glm::ivec2& textureAtlasSize, const TextureData* textures)
{
	for (int i = 0; i < textureCount; i++)
	{
		textureSizes[i] = glm::vec2(textures[i].size) /= textureAtlasSize;
		glm::vec2 start = glm::vec2(textures[i].position) /= textureAtlasSize;
		glm::vec2 end = start + textureSizes[i];

		texCoords[i][0] = { start.x, end.y   };
		texCoords[i][1] = { end.x,   end.y   };
		texCoords[i][2] = { end.x,   start.y };
		texCoords[i][3] = { start.x, start.y };
	}
}
