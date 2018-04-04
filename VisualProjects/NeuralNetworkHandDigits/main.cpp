#include <iostream>
#include <windows.h>

#include "DataLoader.h"
#include "Network.h"
#include "VectorOperators.h"

int main()
{
	std::cout << "Program start" << std::endl;

	DataLoader* loader = new DataLoader();

	std::vector<std::array<std::vector<double>, 2>> data = loader->LoadData("../../MNIST data/train-data-pixels-value", "../../MNIST data/train-data-numbers", 60000);
	std::vector<std::array<std::vector<double>, 2>> trainData(data.begin(), data.begin() + 50000);
	std::vector<std::array<std::vector<double>, 2>> evaluationData(data.begin() + 50000, data.end());

	std::vector<std::array<std::vector<double>, 2>> testData = loader->LoadData("../../MNIST data/test-data-pixels-value", "../../MNIST data/test-data-numbers", 10000);

	/*for (int idx = 0; idx < 1000; ++idx)
	{
		loader->PrintImage(data[idx][0]);

		Sleep(1000);
		system("cls");
	}*/

	/*for (int idx = 0; idx < 1000; ++idx)
	{
		loader->PrintLabel(data[idx][1]);

		Sleep(1000);
		system("cls");
	}*/

	Network* net = new Network({ 784, 30, 10 });
	net->StartLearning(trainData, 30, 3.0, 10, testData);

	std::cin.ignore();
	return 0;
}
