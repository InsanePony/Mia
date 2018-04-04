#include <random>
#include <algorithm>
#include <iostream>

#include "Network.h"
#include "DataLoader.h"
#include "VectorOperators.h"

Network::Network(std::vector<unsigned int> networkForm)
{
	m_vuiNetwork = networkForm;

	m_uiNumberLayers = (unsigned int)networkForm.size();

	std::random_device rd;
	std::default_random_engine generator(rd());
	std::normal_distribution<double> distribution(0.0, 1.0);

	// setup biases
	for (unsigned int i = 1; i < m_uiNumberLayers; ++i)
	{
		std::vector<double> currLayerBiases;

		unsigned int size = networkForm[i];
		currLayerBiases.resize(size);

		for (unsigned int j = 0; j < size; ++j)
			currLayerBiases[j] = distribution(generator);

		m_vvfBiases.push_back(currLayerBiases);
	}

	// setup weights
	for (unsigned int i = 0; i < m_uiNumberLayers - 1; ++i)
	{
		std::vector<double> currLayerWeights;

		unsigned int size = networkForm[i] * networkForm[i + 1];
		currLayerWeights.resize(size);

		for (unsigned int j = 0; j < size; ++j)
			currLayerWeights[j] = distribution(generator);

		m_vvfWeights.push_back(currLayerWeights);
	}
}

void Network::StartLearning(std::vector<std::array<std::vector<double>, 2>> trainingData, unsigned int numberOfGenerations, double learningRate, unsigned int batchSize, std::vector<std::array<std::vector<double>, 2>> const& testData)
{
	std::cout << "Start learning phase" << std::endl;

	// loop on each generation
	for (unsigned int genIdx = 0; genIdx < numberOfGenerations; ++genIdx)
	{
		std::random_shuffle(trainingData.begin(), trainingData.end());
		
		//std::cout << "Batch ";
		unsigned int size = (unsigned int)trainingData.size() / batchSize;
		for (unsigned int batchIdx = 0; batchIdx < size; ++batchIdx)
		{
			unsigned int startIdx = batchIdx * batchSize;
			unsigned int endIdx = startIdx + batchSize;

			/*int number = batchIdx + 1;
			std::cout << number;*/

			UpdateNetworkFromBatch({ trainingData.begin() + startIdx, trainingData.begin() + endIdx }, learningRate);

			/*std::cout << "\b";
			while (number /= 10)
				std::cout << "\b";*/
		}

		if (testData.size() > 0)
		{
			std::cout << "\nGeneration " << genIdx + 1 << " : ";
			Evaluate(testData);
		}
		else
			std::cout << "\nGeneration " << genIdx + 1 << " complete." << std::endl;
	}
}

void Network::Evaluate(std::vector<std::array<std::vector<double>, 2>> const& data)
{
	unsigned int correctResults = 0;

	unsigned int size = (unsigned int)data.size();
	for (unsigned int idx = 0; idx < size; ++idx)
	{
		std::vector<double> inputs = data[idx][0];
		std::vector<double> label = data[idx][1];

		/*DataLoader::PrintImage(inputs);
		DataLoader::PrintLabel(label);*/

		std::vector<double> outputs = OutputFromInput(inputs);

		unsigned int networkNumber = (unsigned int)std::distance(outputs.begin(), std::max_element(outputs.begin(), outputs.end()));
		unsigned int labelNumber = (unsigned int)(std::find(label.begin(), label.end(), 1.f) - label.begin());

		if (networkNumber == labelNumber)
			++correctResults;
	}

	std::cout << correctResults << " / " << size << std::endl;
}

std::vector<double> Network::OutputFromInput(std::vector<double> inputs)
{
	std::vector<double> outputs;

	// Loop on each layer wich can provide an output
	for (unsigned int layerIdx = 1; layerIdx < m_uiNumberLayers; ++layerIdx)
	{
		outputs.clear();

		unsigned int numberNeuron = m_vuiNetwork[layerIdx];

		// loop on each neuron
		for (unsigned int neuronIdx = 0; neuronIdx < numberNeuron; ++neuronIdx)
		{
			unsigned int numberInput = m_vuiNetwork[layerIdx - 1];

			double sigmaWeightsInputs = 0.f;

			// loop on each input
			for (unsigned int inputIdx = 0; inputIdx < numberInput; ++inputIdx)
			{
				unsigned int weightIdx = inputIdx + (neuronIdx * numberInput);
				sigmaWeightsInputs += m_vvfWeights[layerIdx - 1][weightIdx] * inputs[inputIdx];
			}

			sigmaWeightsInputs += m_vvfBiases[layerIdx - 1][neuronIdx];

			outputs.push_back(Sigmoid(sigmaWeightsInputs));
		}

		inputs = outputs;
	}

	return outputs;
}
void Network::Backpropagation(std::vector<std::vector<double>> &weights, std::vector<std::vector<double>> &biases, std::vector<double> const& image, std::vector<double> const& label)
{
	std::vector<double> activation(image.begin(), image.end());
	std::vector<double> expectedOutput(label.begin(), label.end());

	std::vector<double> outputs = std::vector<double>();

	std::vector<std::vector<double>> activations = std::vector<std::vector<double>>();
	activations.push_back(activation);

	// similar to OutputFromInput function
	for (unsigned int layerIdx = 1; layerIdx < m_uiNumberLayers; ++layerIdx)
	{
		outputs.clear();

		unsigned int numberNeuron = m_vuiNetwork[layerIdx];

		for (unsigned int neuronIdx = 0; neuronIdx < numberNeuron; ++neuronIdx)
		{
			unsigned int numberActivation = m_vuiNetwork[layerIdx - 1];

			double sigmaWeightsActivations = 0.f;

			for (unsigned int activationIdx = 0; activationIdx < numberActivation; ++activationIdx)
			{
				unsigned int weightIdx = activationIdx + (neuronIdx * numberActivation);

				sigmaWeightsActivations += m_vvfWeights[layerIdx - 1][weightIdx] * activation[activationIdx];
			}

			sigmaWeightsActivations += m_vvfBiases[layerIdx - 1][neuronIdx];

			outputs.push_back(Sigmoid(sigmaWeightsActivations));
		}

		activation = outputs;

		activations.push_back(activation);
	}

	// backward pass
	std::vector<double> cost = CostFunction(activations.back(), expectedOutput);

	int size = m_vuiNetwork[m_uiNumberLayers - 1];

	std::vector<double> delta;
	delta.resize(size);

	for (int idx = 0; idx < size; ++idx)
		delta[idx] = activation[idx] * (1.0 - activation[idx]) * cost[idx];
	
	biases.back() = delta;


	std::vector<double> deltaWeight;
	deltaWeight.resize(m_vvfWeights.back().size());

	std::vector<double> const& beforeLastActivation = activations[m_uiNumberLayers - 2];
	int beforeLastActivationSize = m_vuiNetwork[m_uiNumberLayers - 2];
	size = size * beforeLastActivationSize;
	for (int idx = 0; idx < size; ++idx)
	{
		int rowIdx = idx / beforeLastActivationSize;
		int columnIdx = idx % beforeLastActivationSize;

		deltaWeight[idx] = delta[rowIdx] * beforeLastActivation[columnIdx];
	}

	weights.back() = deltaWeight;


	for (int layerIdx = m_uiNumberLayers - 3; layerIdx >= 0; --layerIdx)
	{
		std::vector<double> transposedWeights = Utility::Transpose(m_vvfWeights[layerIdx + 1], m_vuiNetwork[layerIdx + 2], m_vuiNetwork[layerIdx + 1]);

		std::vector<double> currDelta;
		currDelta.resize(m_vuiNetwork[layerIdx + 1]);

		// calculate delta
		std::vector<double> currActivation = activations[layerIdx + 1];
		for (unsigned int neuronIdx = 0; neuronIdx < m_vuiNetwork[layerIdx + 1]; ++neuronIdx)
		{
			double sigmoidDerivativeZVector = currActivation[neuronIdx] * (1.0 - currActivation[neuronIdx]);

			int nbColumn = m_vuiNetwork[layerIdx + 2];
			for (int columnIdx = 0; columnIdx < nbColumn; ++columnIdx)
				currDelta[neuronIdx] += transposedWeights[neuronIdx * nbColumn + columnIdx] * delta[columnIdx];

			currDelta[neuronIdx] *= sigmoidDerivativeZVector;
		}

		biases[layerIdx] = currDelta;

		deltaWeight.clear();
		deltaWeight.resize(m_vvfWeights[layerIdx].size());

		currActivation = activations[layerIdx];
		int currActivationSize = (int)currActivation.size();
		size = (int)currDelta.size() * currActivationSize;
		for (int idx = 0; idx < size; ++idx)
		{
			int rowIdx = idx / currActivationSize;
			int columnIdx = idx % currActivationSize;

			deltaWeight[idx] = currDelta[rowIdx] * currActivation[columnIdx];
		}

		weights[layerIdx] = deltaWeight;
	}
}
void Network::UpdateNetworkFromBatch(std::vector<std::array<std::vector<double>, 2>> const& batch, double learningRate)
{
	// create a copy of weights but filled with 0
	std::vector<std::vector<double>> updatedWeights = m_vvfWeights;

	int weightsSize = (int)updatedWeights.size();
	for (int idx = 0; idx < weightsSize; ++idx)
		std::fill(updatedWeights[idx].begin(), updatedWeights[idx].end(), 0.f);

	// create a copy of biases but filled with 0
	std::vector<std::vector<double>> updatedBiases = m_vvfBiases;

	int biasesSize = (int)updatedBiases.size();
	for (int idx = 0; idx < biasesSize; ++idx)
		std::fill(updatedBiases[idx].begin(), updatedBiases[idx].end(), 0.f);

	// loop on each pair of batch
	int batchSize = (int)batch.size();
	for (int pairIdx = 0; pairIdx < batchSize; ++pairIdx)
	{
		std::vector<double> image = batch[pairIdx][0];
		std::vector<double> label = batch[pairIdx][1];

		std::vector<std::vector<double>> deltaWeights = m_vvfWeights;

		for (int idx = 0; idx < weightsSize; ++idx)
			std::fill(deltaWeights[idx].begin(), deltaWeights[idx].end(), 0.f);

		std::vector<std::vector<double>> deltaBiases = m_vvfBiases;

		for (int idx = 0; idx < biasesSize; ++idx)
			std::fill(deltaBiases[idx].begin(), deltaBiases[idx].end(), 0.f);

		Backpropagation(deltaWeights, deltaBiases, image, label);

		// sum of weights given by backpropagation (same for biases)
		for (int weightIdx = 0; weightIdx < weightsSize; ++weightIdx)
		{
			int neuronWeightsSize = (int)updatedWeights[weightIdx].size();
			for (int inputIdx = 0; inputIdx < neuronWeightsSize; ++inputIdx)
				updatedWeights[weightIdx][inputIdx] += deltaWeights[weightIdx][inputIdx];

			int neuronBiasesSize = (int)updatedBiases[weightIdx].size();
			for (int neuronIdx = 0; neuronIdx < neuronBiasesSize; ++neuronIdx)
				updatedBiases[weightIdx][neuronIdx] += deltaBiases[weightIdx][neuronIdx];
		}
	}

	// new weights and biases by applying stochastic gradient descent
	for (int weightIdx = 0; weightIdx < weightsSize; ++weightIdx)
	{
		int neuronWeightsSize = (int)updatedWeights[weightIdx].size();
		for (int inputIdx = 0; inputIdx < neuronWeightsSize; ++inputIdx)
			m_vvfWeights[weightIdx][inputIdx] -= (learningRate / batchSize) * updatedWeights[weightIdx][inputIdx];

		int neuronBiasesSize = (int)updatedBiases[weightIdx].size();
		for (int neuronIdx = 0; neuronIdx < neuronBiasesSize; ++neuronIdx)
			m_vvfBiases[weightIdx][neuronIdx] -= (learningRate / batchSize) * updatedBiases[weightIdx][neuronIdx];
	}
}

std::vector<double> Network::CostFunction(std::vector<double> const& networkOutput, std::vector<double> const& expectedOutput)
{
	return networkOutput - expectedOutput;
}
double Network::Sigmoid(double value)
{
	return 1.0 / (1.0 + exp(-value));
}
