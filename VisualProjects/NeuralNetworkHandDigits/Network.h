#pragma once

#include <vector>

class Network
{
public:
	Network() = delete;
	Network(std::vector<unsigned int> networkForm);
	~Network() = default;

private:
	unsigned int m_uiNumberLayers;

	std::vector<std::vector<float>> m_vvdBiases;
	std::vector<std::vector<float>> m_vvdWeights;
};