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

		m_vvfBiases.push_back(currLayerBiases);
	}

	for (unsigned int i = 0; i < m_uiNumberLayers - 1; ++i)
	{
		std::vector<float> currLayerWeights;

		for (unsigned int j = 0; j < networkForm[i] * networkForm[i + 1]; ++j)
			currLayerWeights.push_back(distribution(generator));

		m_vvfWeights.push_back(currLayerWeights);
	}
}

std::vector<float> Network::OutputFromInput(std::vector<float> inputs)
{
	std::vector<float> outputs;

	// Loop on each layer that can provide an output
	for (unsigned int layerIdx = 1; layerIdx < m_uiNumberLayers; ++layerIdx)
	{
		outputs.clear();

		// loop on each neuron
		for (unsigned int neuronIdx = 0; neuronIdx < m_vuiNetwork[layerIdx]; ++neuronIdx)
		{
			unsigned int numberInputs = m_vuiNetwork[layerIdx - 1];

			float sigmaWeightsInputs = 0.f;

			// loop on each input
			for (unsigned int inputIdx = 0; inputIdx < numberInputs; ++inputIdx)
			{
				int weightIdx = inputIdx + (neuronIdx * numberInputs);
				sigmaWeightsInputs += m_vvfWeights[layerIdx][weightIdx] * inputs[weightIdx];
			}

			sigmaWeightsInputs += m_vvfBiases[layerIdx][neuronIdx];

			outputs.push_back(Sigmoid(sigmaWeightsInputs));
		}

		inputs = outputs;
	}

	return outputs;
}

float Network::Sigmoid(float value)
{
	return 1.f / (1.f + exp(-value));
}
float Network::SigmoidDerivative(float value)
{
	return Sigmoid(value) * (1.f - Sigmoid(value));
}
