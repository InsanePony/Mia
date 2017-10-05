#include <iostream>
#include <windows.h>

#include "DataLoader.h"
#include "Network.h"

int main()
{
	std::cout << "Program start" << std::endl;

	DataLoader* loader = new DataLoader();

	std::vector<std::array<std::vector<unsigned int>, 2>> data = loader->LoadData("../../MNIST data/train-data-pixels-value", "../../MNIST data/train-data-numbers", 1000);

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

	Network* net = new Network({ 2, 3, 2 });

	std::cin.ignore();
	return 0;
}
