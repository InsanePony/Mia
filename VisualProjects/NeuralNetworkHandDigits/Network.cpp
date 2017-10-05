#include <random>

#include "Network.h"

Network::Network(std::vector<unsigned int> networkForm)
{
	m_vuiNetwork = networkForm;

	m_uiNumberLayers = (unsigned int)networkForm.size();

	std::default_random_engine generator;
	std::normal_distribution<float> distribution(0.f, 1.f);

	for (unsigned int i = 1; i < m_uiNumberLayers; ++i)
	{
		std::vector<float> currLayerBiases;

		for (unsigned int j = 0; j < networkForm[i]; ++j)
			currLayerBiases.push_back(distribution(generator));

		m_vvdBiases.push_back(currLayerBiases);
	}

	for (unsigned int i = 0; i < m_uiNumberLayers - 1; ++i)
	{
		std::vector<float> currLayerWeights;

		for (unsigned int j = 0; j < networkForm[i] * networkForm[i + 1]; ++j)
			currLayerWeights.push_back(distribution(generator));

		m_vvdWeights.push_back(currLayerWeights);
	}
}

float Network::Sigmoid(float value)
{
	return 1.f / (1.f + exp(-value));
}
