#include "TextureAtlas.h"

#include <string>

#include "Rendering/Renderer.h"

TextureAtlas::TextureAtlas()
	: maxTextureSize(Renderer::getMaxTextureSize()), root(new TextureNode(glm::ivec2(), maxTextureSize))
{

}

glm::ivec2 TextureAtlas::addTexture(std::shared_ptr<Texture> texture)
{
	glm::ivec2 textureSize = glm::ivec2(texture->getWidth(), texture->getHeight());

	while ((textureSize.x < atlasTextureSize.x || textureSize.y < atlasTextureSize.y) ||
		(atlasTextureSize.x < maxTextureSize.x || atlasTextureSize.y < maxTextureSize.y))
	{
		TextureNode* node = addTexture(root.get(), texture, textureSize);
		if (node != nullptr)
			return node->position;
		else
			atlasTextureSize *= 2; // Keep the texture size a power of 2
	}

	// If this happens, the texture can not fit on the GPU, this is very bad
	return glm::ivec2(-1);
}

// From: https://straypixels.net/texture-packing-for-fonts/
TextureAtlas::TextureNode* TextureAtlas::addTexture(TextureNode* node, const std::shared_ptr<Texture>& texture, const glm::ivec2& size)
{
	// If the node has a texture, it can only be a leaf node, so don't bother
	if (node->texture != nullptr)
	{
		return nullptr;
	}
	// If the node has both children, search them for an opening
	else if (node->left != nullptr && node->right != nullptr)
	{
		TextureNode* newLeftNode = addTexture(node->left.get(), texture, size);
		return newLeftNode != nullptr ? newLeftNode : addTexture(node->right.get(), texture, size);
	}
	// If an opening has been found
	else
	{
		// Get the real size of the opening
		glm::ivec2 realSize(node->size);
		if (node->position.x + node->size.x == maxTextureSize.x)
			realSize.x = atlasTextureSize.x - node->position.x;
		if (node->position.y + node->size.y == maxTextureSize.y)
			realSize.y = atlasTextureSize.y - node->position.y;

		// If the size of the opening (which may technically be the max texture size) is the same size as the texture
		if (node->size == size)
		{
			node->texture = texture;
			return node;
		}
		// This opening is not big enough
		else if (realSize.x < size.x || realSize.y < size.y)
		{
			return nullptr;
		}
		// This opening is bigger than the texture
		else
		{
			glm::ivec2 remainingSize = realSize - size;
			bool splitVertically = remainingSize.x < remainingSize.y;

			// If the opening is the same size as the texture
			if (remainingSize.x == 0 && remainingSize.y == 0)
				splitVertically = node->size.x <= node->size.y;

			// Get the right position and size of the opening and empty space
			TextureNode* left;
			TextureNode* right;
			if (splitVertically)
			{
				left = new TextureNode(node->position, { node->size.x, size.y });
				right = new TextureNode({ node->position.x, node->position.y + size.y }, { node->size.x, node->size.y - size.y });
			}
			else
			{
				left = new TextureNode(node->position, { size.x, node->size.y });
				right = new TextureNode({ node->position.x + size.x, node->position.y }, { node->size.x - size.x, node->size.y });
			}

			node->left.reset(left);
			node->right.reset(right);
			return addTexture(node->left.get(), texture, size);
		}
	}
}

Texture** TextureAtlas::create(int mipmapLevels)
{
	Texture** atlasTextures = nullptr;
	if (mipmapLevels > 0)
	{
		atlasTextures = new Texture*[mipmapLevels];
		for (int i = 0; i < mipmapLevels; i++)
			atlasTextures[i] = new Texture(atlasTextureSize.x >> i, atlasTextureSize.y >> i, 4);
		putTexture(root.get(), atlasTextures, mipmapLevels);
	}
	return atlasTextures;
}

void TextureAtlas::putTexture(TextureNode* node, Texture** atlasTextures, int mipmapLevels)
{
	if (node != nullptr)
	{
		if (node->texture != nullptr)
		{
			// Yes, copying the original texture is a waste of memory,
			// but it makes coding it easier.
			Texture* texture = new Texture(*(node->texture));

			for (int i = 0; i < mipmapLevels && texture != nullptr && texture; i++)
			{
				// This is... finally, where textures are copied
				atlasTextures[i]->setSubregion(*texture, node->position.x >> i, node->position.y >> i);
				Texture* newTexture = texture->createMipmap();
				delete texture;
				texture = newTexture;
			}

			delete texture;
		}
		// Since a node with a texture has no children, don't try to copy their
		// non-existent textures, because they themselves don't exist.
		else
		{
			putTexture(node->left.get(), atlasTextures, mipmapLevels);
			putTexture(node->right.get(), atlasTextures, mipmapLevels);
		}
	}
}
