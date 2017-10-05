#pragma once

#include <vector>

class Network
{
public:
	Network() = delete;
	Network(std::vector<unsigned int> networkForm);
	~Network() = default;

private:
	float Sigmoid(float value);

	std::vector<unsigned int> m_vuiNetwork;
	unsigned int m_uiNumberLayers;

	std::vector<std::vector<float>> m_vvdBiases;
	std::vector<std::vector<float>> m_vvdWeights;
};