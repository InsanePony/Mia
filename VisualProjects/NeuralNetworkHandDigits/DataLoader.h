#pragma once

#define DATALOADER_FUNCS_DLL __declspec(dllexport)

#include <vector>
#include <array>
#include <string>

class DataLoader
{
public:
	DATALOADER_FUNCS_DLL DataLoader() = default;
	DATALOADER_FUNCS_DLL ~DataLoader() = default;

	DATALOADER_FUNCS_DLL std::vector<std::array<std::vector<double>, 2>> LoadData(std::string const& imagesFilePath, std::string const& labelsFilePath, int desiredNumberData);

	DATALOADER_FUNCS_DLL static void PrintImage(std::vector<double> image);
	DATALOADER_FUNCS_DLL static void PrintLabel(std::vector<double> label);

private:
	std::vector<std::vector<double>> LoadImages(std::string const& filePath, int numberOfImages);
	std::vector<std::vector<double>> LoadLabels(std::string const& filePath, int numberOfLabels);

	int ConvertToInt(int value);
	std::vector<double> VectorizeLabel(unsigned int value);
};
