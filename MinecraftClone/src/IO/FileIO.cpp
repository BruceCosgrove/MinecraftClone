#include "FileIO.h"

#include <fstream>

std::string FileIO::readFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (file.is_open())
	{
		// Get the file size
		file.seekg(0, std::ios::end);
		size_t size = file.tellg();
		file.seekg(0, std::ios::beg);

		// Read the file into the string
		std::string contents(size, ' ');
		file.read(&contents[0], size);
		file.close();
		return contents;
	}
	return std::string();
}
