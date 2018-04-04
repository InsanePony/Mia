#pragma once

#include <string>

#include "Network.h"

class NetworkSaver
{
public:
	NetworkSaver() = delete;
	NetworkSaver(NetworkSaver const&) = delete;
	NetworkSaver(std::string filename, std::vector<unsigned int> networkForm, std::vector<std::vector<double>> biases, std::vector<std::vector<double>> weights);
	~NetworkSaver() = default;
};
