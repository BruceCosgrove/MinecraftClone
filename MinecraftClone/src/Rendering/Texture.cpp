#include "Texture.h"

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

Texture::Texture(const std::string& filePath, int requiredChannels, bool flipVertically)
{
	readFile(filePath, requiredChannels, flipVertically);
}

Texture::Texture(int width, int height, int channels)
{
	create(width, height, channels);
}

Texture::Texture(const Texture& texture)
{
	copy(texture);
}

Texture::~Texture()
{
	delete[] data;
}

bool Texture::readFile(const std::string& filePath, int requiredChannels, bool flipVertically)
{
	stbi_set_flip_vertically_on_load(flipVertically);
	stbi_uc* stbiData = stbi_load(filePath.c_str(), &width, &height, &channels, requiredChannels);
	if (stbiData != nullptr)
	{
		if (data != nullptr)
			delete[] data;
		data = stbiData;

		if (requiredChannels != 0)
			channels = requiredChannels;
		this->filePath = filePath;
		return true;
	}
	return false;
}

bool Texture::writeFile(const std::string& filePath, bool flipVertically)
{
	stbi_flip_vertically_on_write(flipVertically);
	// TODO: let the user decide the output file format
	return data != nullptr && stbi_write_png(filePath.c_str(), width, height, channels, data, 0) != 0;
}

void Texture::create(int width, int height, int channels)
{
	if (data != nullptr)
	{
		delete[] data;
		filePath.clear();
	}

	size_t size = (size_t)width * height * channels;
	data = new unsigned char[size]{ 0 };
	this->width = width;
	this->height = height;
	this->channels = channels;
}

bool Texture::copy(const Texture& texture)
{
	if (texture)
	{
		if (data != nullptr)
			delete[] data;

		width = texture.width;
		height = texture.height;
		channels = texture.channels;
		filePath = texture.filePath;

		size_t size = (size_t)width * height * channels;
		data = new unsigned char[size];
		memcpy_s(data, size, texture.data, size);
		return true;
	}
	return false;
}

bool Texture::setSubregion(const Texture& texture, int positionX, int positionY)
{
	if (channels == texture.channels && positionX + texture.width <= width && positionX >= 0 && positionY + texture.height <= height && positionY >= 0)
	{
		size_t textureIncrement = (size_t)texture.width * channels;
		size_t increment = (size_t)width * channels;

		unsigned char* source = texture.data;
		unsigned char* destination = data + (((size_t)positionY * width + positionX) * channels);
		for (size_t y = 0; y < texture.height; y++, source += textureIncrement, destination += increment)
			memcpy_s(destination, textureIncrement, source, textureIncrement);
		return true;
	}
	return false;
}

Texture* Texture::createMipmap()
{
	if (data != nullptr)
	{
		Texture* texture = new Texture(width >> 1, height >> 1, channels);

		for (int y = 0; y < texture->height; y++)
		{
			for (int x = 0; x < texture->width; x++)
			{
				int index1 = ((y * 2 + 0) * width + x * 2) * channels;
				int index2 = ((y * 2 + 1) * width + x * 2) * channels;
				int textureIndex = (y * texture->width + x) * channels;

				for (int c = 0; c < channels; c++)
					texture->data[textureIndex + c] = (data[index1 + c] + data[index1 + channels + c] + data[index2 + c] + data[index2 + channels + c]) / 4;
			}
		}

		return texture;
	}
	return nullptr;
}
