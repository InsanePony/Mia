#include <random>
#include <algorithm>

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
void Network::UpdateNetworkFromBatch(std::vector<std::array<std::vector<unsigned int>, 2>> const& batch, float learningRate)
{
	// create a copy of weights but filled with 0
	std::vector<std::vector<float>> updatedWeights = m_vvfWeights;

	int weightsSize = (int)updatedWeights.size();
	for (int idx = 0; idx < weightsSize; ++idx)
		std::fill(updatedWeights[idx].begin(), updatedWeights[idx].end(), 0.f);

	// create a copy of biases but filled with 0
	std::vector<std::vector<float>> updatedBiases = m_vvfBiases;

	int biasesSize = (int)updatedBiases.size();
	for (int idx = 0; idx < biasesSize; ++idx)
		std::fill(updatedBiases[idx].begin(), updatedBiases[idx].end(), 0.f);

	// loop on each pair of batch
	int batchSize = (int)batch.size();
	for (int pairIdx = 0; pairIdx < batchSize; ++pairIdx)
	{
		std::vector<unsigned int> image = batch[pairIdx][0];
		std::vector<unsigned int> label = batch[pairIdx][1];

		std::vector<std::vector<float>> deltaWeights = m_vvfWeights;

		for (int idx = 0; idx < weightsSize; ++idx)
			std::fill(deltaWeights[idx].begin(), deltaWeights[idx].end(), 0.f);

		std::vector<std::vector<float>> deltaBiases = m_vvfBiases;

		for (int idx = 0; idx < biasesSize; ++idx)
			std::fill(deltaBiases[idx].begin(), deltaBiases[idx].end(), 0.f);

		//Backpropagation(deltaWeights, deltaBiases, image, label);

		// sum of weights given by backpropagation (same for biases)
		for (int neuronWeightsIdx = 0; neuronWeightsIdx < weightsSize; ++neuronWeightsIdx)
		{
			int neuronWeightsSize = (int)updatedWeights[neuronWeightsIdx].size();
			for (int weightIdx = 0; weightIdx < neuronWeightsSize; ++weightIdx)
			{
				updatedWeights[neuronWeightsIdx][weightIdx] += deltaWeights[neuronWeightsIdx][weightIdx];
				updatedBiases[neuronWeightsIdx][weightIdx] += deltaBiases[neuronWeightsIdx][weightIdx];
			}
		}
	}

	// new weights and biases by applying stochastic gradient descent
	for (int neuronWeightsIdx = 0; neuronWeightsIdx < weightsSize; ++neuronWeightsIdx)
	{
		int neuronWeightsSize = (int)updatedWeights[neuronWeightsIdx].size();
		for (int weightIdx = 0; weightIdx < neuronWeightsSize; ++weightIdx)
		{
			m_vvfWeights[neuronWeightsIdx][weightIdx] -= (learningRate / batchSize) * updatedWeights[neuronWeightsIdx][weightIdx];
			m_vvfBiases[neuronWeightsIdx][weightIdx] -= (learningRate / batchSize) * updatedBiases[neuronWeightsIdx][weightIdx];
		}
	}
}

float Network::Sigmoid(float value)
{
	return 1.f / (1.f + exp(-value));
}
float Network::SigmoidDerivative(float value)
{
	return Sigmoid(value) * (1.f - Sigmoid(value));
}
