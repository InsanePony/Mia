#pragma once

#include <vector>

class Network
{
public:
	Network() = delete;
	Network(std::vector<unsigned int> networkForm);
	~Network() = default;

private:
	std::vector<float> OutputFromInput(std::vector<float> inputs);

	float Sigmoid(float value);

	std::vector<unsigned int> m_vuiNetwork;
	unsigned int m_uiNumberLayers;

	std::vector<std::vector<float>> m_vvfBiases;
	std::vector<std::vector<float>> m_vvfWeights;
};