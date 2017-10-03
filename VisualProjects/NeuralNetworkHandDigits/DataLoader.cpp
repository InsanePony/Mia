#include <iostream>
#include <fstream>

#include "DataLoader.h"

std::vector<std::vector<unsigned int>> DataLoader::LoadFile(std::string const& relativeFilePath, int numberOfImages)
{
	std::cout << "Open file : " << relativeFilePath << std::endl;

	std::ifstream file(relativeFilePath, std::ios::binary);

	if (file.is_open())
	{
		int magicNumber = 0;
		file.read((char*)&magicNumber, 4);
		magicNumber = ConvertToInt(magicNumber);

		int nbImagesInFile = 0;
		file.read((char*)&nbImagesInFile, 4);
		nbImagesInFile = ConvertToInt(nbImagesInFile);

		if (nbImagesInFile < numberOfImages)
		{
			std::cout << "Not enough images in file" << std::endl;
			return std::vector<std::vector<unsigned int>>();
		}

		int nbRows = 0;
		file.read((char*)&nbRows, 4);
		nbRows = ConvertToInt(nbRows);

		int nbColumns = 0;
		file.read((char*)&nbColumns, 4);
		nbColumns = ConvertToInt(nbColumns);

		int nbPixels = nbRows * nbColumns;

		std::vector<std::vector<unsigned int>> data;
		data.resize(numberOfImages, std::vector<unsigned int>(nbPixels));

		for (int imageIdx = 0; imageIdx < numberOfImages; ++imageIdx)
		{
			for (int rowIdx = 0; rowIdx < nbRows; ++rowIdx)
			{
				for (int columnIdx = 0; columnIdx < nbColumns; ++columnIdx)
				{
					unsigned char pixelColor = 0;
					file.read((char*)&pixelColor, 1);
					data[imageIdx][(rowIdx * nbRows) + columnIdx] = (unsigned int)pixelColor;
				}
			}
		}

		return data;
	}

	std::cout << "Can't open file" << std::endl;
	return std::vector<std::vector<unsigned int>>();
}

void DataLoader::PrintImage(std::vector<unsigned int> image)
{
	int count = 0;

	for (int idx = 0; idx < 784; ++idx)
	{
		++count;

		std::cout << image[idx] << " ";

		if (image[idx] < 10)
			std::cout << " ";
		if (image[idx] < 100)
			std::cout << " ";

		if (count == 28)
		{
			std::cout << "\n" << std::endl;
			count = 0;
		}
	}
}

int DataLoader::ConvertToInt(int value)
{
	unsigned char c1, c2, c3, c4;

	c1 = value & 255;
	c2 = (value >> 8) & 255;
	c3 = (value >> 16) & 255;
	c4 = (value >> 24) & 255;

	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}
std::vector<unsigned int> DataLoader::VectorizeLabel(unsigned int value)
{
	std::vector<unsigned int> vectorizedLabel = std::vector<unsigned int>(10, 0);

	vectorizedLabel[value] = 1;

	return vectorizedLabel;
}
