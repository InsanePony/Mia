#pragma once

#define NETWORK_FUNCS_DLL __declspec(dllexport)

#include <vector>
#include <array>

#include "NetworkLoader.h"

class Network
{
public:
	NETWORK_FUNCS_DLL Network() = delete;
	NETWORK_FUNCS_DLL Network(Network const&) = delete;
	NETWORK_FUNCS_DLL Network(std::vector<unsigned int> networkForm);
	NETWORK_FUNCS_DLL Network(NetworkLoader* netLoader);
	NETWORK_FUNCS_DLL ~Network() = default;

	// testData = used data to evaluate neural network after each generation
	NETWORK_FUNCS_DLL void StartLearning(std::vector<std::array<std::vector<double>, 2>> trainingData, unsigned int numberOfGenerations, double learningRate, unsigned int batchSize, std::vector<std::array<std::vector<double>, 2>> const& testData = {}); // = stochastic gradient descent

	NETWORK_FUNCS_DLL void Evaluate(std::vector<std::array<std::vector<double>, 2>> const& data);

	NETWORK_FUNCS_DLL int GetResponse(std::vector<double> number);

private:
	std::vector<double> OutputFromInput(std::vector<double> inputs);
	void Backpropagation(std::vector<std::vector<double>> &weights, std::vector<std::vector<double>> &biases, std::vector<double> const& image, std::vector<double> const& label);
	void UpdateNetworkFromBatch(std::vector<std::array<std::vector<double>, 2>> const& batch, double learningRate);

	std::vector<double> CostFunction(std::vector<double> const& networkOutput, std::vector<double> const& expectedOutput);
	double Sigmoid(double value);

	std::vector<unsigned int> m_vuiNetwork;
	unsigned int m_uiNumberLayers;

	std::vector<std::vector<double>> m_vvdBiases;
	std::vector<std::vector<double>> m_vvdWeights;
};