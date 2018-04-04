#pragma once

#include <vector>

class NetworkLoader
{
public:
	NetworkLoader() = delete;
	NetworkLoader(NetworkLoader const&) = delete;
	NetworkLoader(const char* filePath);
	~NetworkLoader() = default;

	std::vector<unsigned int> GetNetworkForm() { return m_vuiNetworkForm; }
	unsigned int GetNumberOfLayers() { return m_uiNumberOfLayers; }
	std::vector<std::vector<double>> GetBiases() { return m_vvdBiases; }
	std::vector<std::vector<double>> GetWeights() { return m_vvdWeights; }

private:
	std::vector<unsigned int> m_vuiNetworkForm;
	unsigned int m_uiNumberOfLayers;

	std::vector<std::vector<double>> m_vvdBiases;
	std::vector<std::vector<double>> m_vvdWeights;
};
