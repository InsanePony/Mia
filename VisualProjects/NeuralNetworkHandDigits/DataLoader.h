#pragma once

#include <vector>
#include <array>
#include <string>

class DataLoader
{
public:
	DataLoader() = default;
	~DataLoader() = default;

	std::vector<std::array<std::vector<unsigned int>, 2>> LoadData(std::string const& imagesFilePath, std::string const& labelsFilePath, int desiredNumberData);

	void PrintImage(std::vector<unsigned int> image);
	void PrintLabel(std::vector<unsigned int> label);

private:
	std::vector<std::vector<unsigned int>> LoadImages(std::string const& filePath, int numberOfImages);
	std::vector<std::vector<unsigned int>> LoadLabels(std::string const& filePath, int numberOfLabels);

	int ConvertToInt(int value);
	std::vector<unsigned int> VectorizeLabel(unsigned int value);
};
