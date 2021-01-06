#pragma once

#include <string>

class Texture
{
public:
	Texture() = default;
	Texture(const std::string& filePath, int requiredChannels = 0, bool flipVertically = false);
	Texture(int width, int height, int channels);
	Texture(const Texture& texture);
	~Texture();

	bool readFile(const std::string& filePath, int requiredChannels = 0, bool flipVertically = false);
	bool writeFile(const std::string& filePath, bool flipVertically = false);
	void create(int width, int height, int channels);
	bool copy(const Texture& texture);

	bool setSubregion(const Texture& texture, int positionX, int positionY);

	Texture* createMipmap();

	inline const std::string& getFilePath() const { return filePath; }
	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
	inline int getChannels() const { return channels; }
	inline unsigned char* getData() const { return data; }

	inline operator bool() const { return data != nullptr; }
private:
	std::string filePath;

	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char* data = nullptr;
};
