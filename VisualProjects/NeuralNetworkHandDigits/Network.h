#pragma once

#include <vector>
#include <array>

class Network
{
public:
	Network() = delete;
	Network(std::vector<unsigned int> networkForm);
	~Network() = default;

private:
	std::vector<float> OutputFromInput(std::vector<float> inputs);
	void UpdateNetworkFromBatch(std::vector<std::array<std::vector<unsigned int>, 2>> const& batch, float learningRate);

	float Sigmoid(float value);
	float SigmoidDerivative(float value);

	std::vector<unsigned int> m_vuiNetwork;
	unsigned int m_uiNumberLayers;

	std::vector<std::vector<float>> m_vvfBiases;
	std::vector<std::vector<float>> m_vvfWeights;
};