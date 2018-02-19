#pragma once

#include <vector>
#include <array>

class Network
{
public:
	Network() = delete;
	Network(std::vector<unsigned int> networkForm);
	~Network() = default;

	// testData = used data to evaluate neural network after each generation
	void StartLearning(std::vector<std::array<std::vector<double>, 2>> trainingData, unsigned int numberOfGenerations, double learningRate, unsigned int batchSize, std::vector<std::array<std::vector<double>, 2>> const& testData = {}); // = stochastic gradient descent

	void Evaluate(std::vector<std::array<std::vector<double>, 2>> const& data);

private:
	std::vector<double> OutputFromInput(std::vector<double> inputs);
	void Backpropagation(std::vector<std::vector<double>> &weights, std::vector<std::vector<double>> &biases, std::vector<double> const& image, std::vector<double> const& label);
	void UpdateNetworkFromBatch(std::vector<std::array<std::vector<double>, 2>> const& batch, double learningRate);

	std::vector<double> CostFunction(std::vector<double> const& networkOutput, std::vector<double> const& expectedOutput);
	double Sigmoid(double value);

	std::vector<unsigned int> m_vuiNetwork;
	unsigned int m_uiNumberLayers;

	std::vector<std::vector<double>> m_vvfBiases;
	std::vector<std::vector<double>> m_vvfWeights;
};