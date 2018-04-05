#pragma once

#define NETWORKSAVER_FUNCS_DLL __declspec(dllexport)

#include <string>

#include "Network.h"

class NetworkSaver
{
public:
	NETWORKSAVER_FUNCS_DLL NetworkSaver() = delete;
	NETWORKSAVER_FUNCS_DLL NetworkSaver(NetworkSaver const&) = delete;
	NETWORKSAVER_FUNCS_DLL NetworkSaver(std::string filename, std::vector<unsigned int> networkForm, std::vector<std::vector<double>> biases, std::vector<std::vector<double>> weights);
	NETWORKSAVER_FUNCS_DLL ~NetworkSaver() = default;
};
