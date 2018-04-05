#pragma once

#define NETWORKLOADER_FUNCS_DLL __declspec(dllexport)

#include <vector>

class NetworkLoader
{
public:
	NETWORKLOADER_FUNCS_DLL NetworkLoader() = delete;
	NETWORKLOADER_FUNCS_DLL NetworkLoader(NetworkLoader const&) = delete;
	NETWORKLOADER_FUNCS_DLL NetworkLoader(const char* filePath);
	NETWORKLOADER_FUNCS_DLL ~NetworkLoader() = default;

	NETWORKLOADER_FUNCS_DLL std::vector<unsigned int> GetNetworkForm() { return m_vuiNetworkForm; }
	NETWORKLOADER_FUNCS_DLL unsigned int GetNumberOfLayers() { return m_uiNumberOfLayers; }
	NETWORKLOADER_FUNCS_DLL std::vector<std::vector<double>> GetBiases() { return m_vvdBiases; }
	NETWORKLOADER_FUNCS_DLL std::vector<std::vector<double>> GetWeights() { return m_vvdWeights; }

private:
	std::vector<unsigned int> m_vuiNetworkForm;
	unsigned int m_uiNumberOfLayers;

	std::vector<std::vector<double>> m_vvdBiases;
	std::vector<std::vector<double>> m_vvdWeights;
};
