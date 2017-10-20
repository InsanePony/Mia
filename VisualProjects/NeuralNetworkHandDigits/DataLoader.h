#pragma once

#include <vector>
#include <array>
#include <string>

class DataLoader
{
public:
	DataLoader() = default;
	~DataLoader() = default;

	std::vector<std::array<std::vector<float>, 2>> LoadData(std::string const& imagesFilePath, std::string const& labelsFilePath, int desiredNumberData);

	void PrintImage(std::vector<float> image);
	void PrintLabel(std::vector<float> label);

private:
	std::vector<std::vector<float>> LoadImages(std::string const& filePath, int numberOfImages);
	std::vector<std::vector<float>> LoadLabels(std::string const& filePath, int numberOfLabels);

	int ConvertToInt(int value);
	std::vector<float> VectorizeLabel(unsigned int value);
};
