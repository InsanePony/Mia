#pragma once

#include <vector>
#include <string>

class DataLoader
{
public:
	DataLoader() = default;
	~DataLoader() = default;

	std::vector<std::vector<unsigned int>> LoadFile(std::string const& relativeFilePath, int numberOfImages);

	void PrintImage(std::vector<unsigned int> image);

private:
	int ConvertToInt(int value);
	std::vector<unsigned int> VectorizeLabel(unsigned int value);
};
