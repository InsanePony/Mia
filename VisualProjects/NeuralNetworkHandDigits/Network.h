#pragma once

#include <vector>
#include <array>

class Network
{
public:
	Network() = delete;
	Network(std::vector<unsigned int> networkForm);
	~Network() = default;

	void Evaluate(std::vector<std::array<std::vector<float>, 2>> const& data);

private:
	std::vector<float> OutputFromInput(std::vector<float> inputs);
	void Backpropagation(std::vector<std::vector<float>> &weights, std::vector<std::vector<float>> &biases, std::vector<unsigned int> image, std::vector<unsigned int> label);
	void UpdateNetworkFromBatch(std::vector<std::array<std::vector<unsigned int>, 2>> const& batch, float learningRate);

	std::vector<float> CostFunction(std::vector<float> const& networkOutput, std::vector<float> const& expectedOutput);
	float Sigmoid(float value);
	float SigmoidDerivative(float value);

	std::vector<unsigned int> m_vuiNetwork;
	unsigned int m_uiNumberLayers;

	std::vector<std::vector<float>> m_vvfBiases;
	std::vector<std::vector<float>> m_vvfWeights;
};