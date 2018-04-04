#include <fstream>
#include <iostream>

#include "NetworkSaver.h"

NetworkSaver::NetworkSaver(std::string filename, std::vector<unsigned int> networkForm, std::vector<std::vector<double>> biases, std::vector<std::vector<double>> weights)
{
	unsigned int numberOfLayers = (unsigned int)networkForm.size();

	std::string directory("../../");
	std::string extension(".mia");
	std::string completePath = directory + filename + extension;

	std::ofstream file;
	file.open(completePath, std::ios::out | std::ios::binary | std::ios::trunc);

	// number of layer
	file.write(reinterpret_cast<const char*>(&numberOfLayers), sizeof(unsigned int));
	if (file.bad())
		std::cout << "File writing error : number of layers" << std::endl;

	// network form
	for (int layerIdx = 0; layerIdx < numberOfLayers; ++layerIdx)
		file.write(reinterpret_cast<const char*>(&networkForm[layerIdx]), sizeof(unsigned int));

	if (file.bad())
		std::cout << "File writing error : networm form" << std::endl;

	// biases
	int biasesSize = (int)biases.size();
	for (int biasesIdx = 0; biasesIdx < biasesSize; ++biasesIdx)
	{
		int layerBiasSize = (int)biases[biasesIdx].size();
		for (int layerBiasIdx = 0; layerBiasIdx < layerBiasSize; ++layerBiasIdx)
			file.write(reinterpret_cast<const char*>(&biases[biasesIdx][layerBiasIdx]), sizeof(double));
	}

	if (file.bad())
		std::cout << "File writing error : biases" << std::endl;

	// weights
	int weightsSize = (int)weights.size();
	for (int weightsIdx = 0; weightsIdx < weightsSize; ++weightsIdx)
	{
		int layerWeightSize = (int)weights[weightsIdx].size();
		for (int layerWeightIdx = 0; layerWeightIdx < layerWeightSize; ++layerWeightIdx)
			file.write(reinterpret_cast<const char*>(&weights[weightsIdx][layerWeightIdx]), sizeof(double));
	}

	if (file.bad())
		std::cout << "File writing error : weights" << std::endl;

	file.close();
}
