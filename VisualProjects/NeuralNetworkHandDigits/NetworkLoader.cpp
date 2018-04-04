#include <fstream>
#include <iostream>

#include "NetworkLoader.h"

NetworkLoader::NetworkLoader(const char* filePath)
{
	std::ifstream file;
	file.open(filePath, std::ios::in | std::ios::binary);

	// number of layer
	file.read(reinterpret_cast<char*>(&m_uiNumberOfLayers), sizeof(unsigned int));

	// network form
	m_vuiNetworkForm = std::vector<unsigned int>();
	m_vuiNetworkForm.resize(m_uiNumberOfLayers);
	for (unsigned int netFormIdx = 0; netFormIdx < m_uiNumberOfLayers; ++netFormIdx)
		file.read(reinterpret_cast<char*>(&m_vuiNetworkForm[netFormIdx]), sizeof(unsigned int));

	// biases
	m_vvdBiases = std::vector<std::vector<double>>();
	for (unsigned int biasesIdx = 1; biasesIdx < m_uiNumberOfLayers; ++biasesIdx)
	{
		int currBiasLayerSize = m_vuiNetworkForm[biasesIdx];
		std::vector<double> currBiasLayer = std::vector<double>();
		currBiasLayer.resize(currBiasLayerSize);

		for (int biasIdx = 0; biasIdx < currBiasLayerSize; ++biasIdx)
			file.read(reinterpret_cast<char*>(&currBiasLayer[biasIdx]), sizeof(double));

		m_vvdBiases.push_back(currBiasLayer);
	}

	// weights
	m_vvdWeights = std::vector<std::vector<double>>();
	for (unsigned int weightsIdx = 0; weightsIdx < m_uiNumberOfLayers - 1; ++weightsIdx)
	{
		int currWeightLayerSize = m_vuiNetworkForm[weightsIdx] * m_vuiNetworkForm[weightsIdx + 1];
		std::vector<double> currWeightLayer = std::vector<double>();
		currWeightLayer.resize(currWeightLayerSize);

		for (int weightIdx = 0; weightIdx < currWeightLayerSize; ++weightIdx)
			file.read(reinterpret_cast<char*>(&currWeightLayer[weightIdx]), sizeof(double));

		m_vvdWeights.push_back(currWeightLayer);
	}

	file.close();
}
