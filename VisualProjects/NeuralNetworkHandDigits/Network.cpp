#include <random>
#include <algorithm>

#include "Network.h"
#include "VectorOperators.h"

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

		unsigned int numberNeuron = m_vuiNetwork[layerIdx];

		// loop on each neuron
		for (unsigned int neuronIdx = 0; neuronIdx < numberNeuron; ++neuronIdx)
		{
			unsigned int numberInput = m_vuiNetwork[layerIdx - 1];

			float sigmaWeightsInputs = 0.f;

			// loop on each input
			for (unsigned int inputIdx = 0; inputIdx < numberInput; ++inputIdx)
			{
				unsigned int weightIdx = inputIdx + (neuronIdx * numberInput);
				sigmaWeightsInputs += m_vvfWeights[layerIdx][weightIdx] * inputs[weightIdx];
			}

			sigmaWeightsInputs += m_vvfBiases[layerIdx][neuronIdx];

			outputs.push_back(Sigmoid(sigmaWeightsInputs));
		}

		inputs = outputs;
	}

	return outputs;
}
void Network::Backpropagation(std::vector<std::vector<float>> &weights, std::vector<std::vector<float>> &biases, std::vector<unsigned int> image, std::vector<unsigned int> label)
{
	std::vector<float> activation(image.begin(), image.end());
	std::vector<float> expectedOutput(label.begin(), label.end());

	std::vector<float> outputs = std::vector<float>();

	std::vector<std::vector<float>> activations = std::vector<std::vector<float>>();
	activations.push_back(activation);

	std::vector<float> sigmasWeightsActivations = std::vector<float>();
	std::vector<std::vector<float>> zVectors = std::vector<std::vector<float>>();

	// similar to OutputFromInput function
	for (unsigned int layerIdx = 1; layerIdx < m_uiNumberLayers; ++layerIdx)
	{
		outputs.clear();
		sigmasWeightsActivations.clear();

		unsigned int numberNeuron = m_vuiNetwork[layerIdx];

		for (unsigned int neuronIdx = 0; neuronIdx < numberNeuron; ++neuronIdx)
		{
			unsigned int numberActivation = m_vuiNetwork[layerIdx - 1];

			float sigmaWeightsActivations = 0.f;

			for (unsigned int activationIdx = 0; activationIdx < numberActivation; ++activationIdx)
			{
				unsigned int weightIdx = activationIdx + (neuronIdx * numberActivation);

				sigmaWeightsActivations += m_vvfWeights[layerIdx][weightIdx] * activation[weightIdx];
			}

			sigmaWeightsActivations += m_vvfBiases[layerIdx][neuronIdx];

			sigmasWeightsActivations.push_back(sigmaWeightsActivations);
			outputs.push_back(Sigmoid(sigmaWeightsActivations));
		}

		activation = outputs;

		zVectors.push_back(sigmasWeightsActivations);
		activations.push_back(activation);
	}

	// backward pass
	std::vector<float> cost = CostFunction(activations.back(), expectedOutput);
	std::vector<float> delta = std::vector<float>();

	std::vector<float> lastZVector = zVectors.back();
	int size = (int)lastZVector.size();
	for (int idx = 0; idx < size; ++idx)
		delta.push_back(cost[idx] * lastZVector[idx]);
	
	biases.back() = delta;


	std::vector<float> deltaWeight;
	deltaWeight.resize(m_vvfWeights.back().size());

	int activationsSize = (int)activations.size();
	std::vector<float> beforeLastActivation = activations[activationsSize - 2];
	int beforeLastActivationSize = (int)beforeLastActivation.size();
	size = (int)delta.size() * beforeLastActivationSize;
	for (int idx = 0; idx < size; ++idx)
	{
		int rowIdx = idx / beforeLastActivationSize;
		int columnIdx = idx % beforeLastActivationSize;

		deltaWeight[idx] = delta[rowIdx] * beforeLastActivation[columnIdx];
	}

	weights.back() = deltaWeight;

	for (unsigned int negativeLayerIdx = 2; negativeLayerIdx < m_uiNumberLayers; ++negativeLayerIdx)
	{
		int layerIdx = activationsSize % negativeLayerIdx;
		std::vector<float> zVector = zVectors[layerIdx];
		
		std::vector<float> transposedWeights = Utility::Transpose(m_vvfWeights[layerIdx], m_vuiNetwork[layerIdx + 1], m_vuiNetwork[layerIdx]);

		int numberNeuron = m_vuiNetwork[layerIdx];
		std::vector<float> currDelta;
		currDelta.resize(numberNeuron);

		for (int neuronIdx = 0; neuronIdx < numberNeuron; ++neuronIdx)
		{
			float sigmoidDerivativeZVector = SigmoidDerivative(zVector[neuronIdx]);

			int nbColumn = m_vuiNetwork[layerIdx + 1];
			for (int columnIdx = 0; columnIdx < nbColumn; ++columnIdx)
				currDelta[neuronIdx] += transposedWeights[neuronIdx * nbColumn + columnIdx] * delta[columnIdx];

			currDelta[neuronIdx] *= sigmoidDerivativeZVector;
		}

		biases[layerIdx] = currDelta;

		deltaWeight.clear();
		deltaWeight.resize(m_vvfWeights[layerIdx - 1].size());

		std::vector<float> currActivation = activations[layerIdx - 1];
		int currActivationSize = (int)currActivation.size();
		size = (int)delta.size() * currActivationSize;
		for (int idx = 0; idx < size; ++idx)
		{
			int rowIdx = idx / currActivationSize;
			int columnIdx = idx % currActivationSize;

			deltaWeight[idx] = delta[rowIdx] * currActivation[columnIdx];
		}

		weights[layerIdx - 1] = deltaWeight;
	}
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

		Backpropagation(deltaWeights, deltaBiases, image, label);

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

std::vector<float> Network::CostFunction(std::vector<float> const& networkOutput, std::vector<float> const& expectedOutput)
{
	return networkOutput - expectedOutput;
}
float Network::Sigmoid(float value)
{
	return 1.f / (1.f + exp(-value));
}
float Network::SigmoidDerivative(float value)
{
	return Sigmoid(value) * (1.f - Sigmoid(value));
}
