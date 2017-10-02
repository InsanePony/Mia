#include <iostream>
#include <windows.h>

#include "DataLoader.h"

int main()
{
	std::cout << "Program start" << std::endl;

	DataLoader* loader = new DataLoader();

	std::vector<std::vector<unsigned int>> data = loader->LoadFile("../../MNIST data/train-data-pixels-value", 1000);

	/*for (int idx = 0; idx < 1000; ++idx)
	{
		loader->PrintImage(data[idx]);

		Sleep(1000);
		system("cls");
	}*/

	std::cin.ignore();
	return 0;
}
