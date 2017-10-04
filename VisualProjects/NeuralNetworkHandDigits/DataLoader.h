#pragma once

#include <vector>
#include <array>
#include <string>

class DataLoader
{
public:
	DataLoader() = default;
	~DataLoader() = default;

	std::vector<std::array<std::vector<unsigned int>, 2>> LoadData(std::string const& imagesFilePath, std::string const& labelsFilePath, int numberOfImages);

	void PrintImage(std::vector<unsigned int> image);
	void PrintLabel(std::vector<unsigned int> label);

private:
	int ConvertToInt(int value);
	std::vector<unsigned int> VectorizeLabel(unsigned int value);
};
