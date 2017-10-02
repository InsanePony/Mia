#include <iostream>

#include "DataLoader.h"

int main()
{
	std::cout << "Program start" << std::endl;

	DataLoader* loader = new DataLoader();

	loader->LoadFile("../../MNIST data/train-data-pixels-value", 1000);

	std::cin.ignore();
	return 0;
}
