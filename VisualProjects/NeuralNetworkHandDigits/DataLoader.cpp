#include <iostream>
#include <fstream>
#include <algorithm>

#include "DataLoader.h"

std::vector<std::array<std::vector<float>, 2>> DataLoader::LoadData(std::string const& imagesFilePath, std::string const& labelsFilePath, int desiredNumberData)
{
	std::vector<std::vector<float>> images = LoadImages(imagesFilePath, desiredNumberData);
	std::vector<std::vector<float>> labels = LoadLabels(labelsFilePath, desiredNumberData);

	std::vector<std::array<std::vector<float>, 2>> data;
	data.resize(desiredNumberData);

	for (int dataIdx = 0; dataIdx < desiredNumberData; ++dataIdx)
		data[dataIdx] = { images[dataIdx], labels[dataIdx] };

	return data;
}

void DataLoader::PrintImage(std::vector<float> image)
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
void DataLoader::PrintLabel(std::vector<float> label)
{
	std::vector<float>::iterator it = std::find(label.begin(), label.end(), 1);

	std::cout << it - label.begin() << std::endl;
}

std::vector<std::vector<float>> DataLoader::LoadImages(std::string const& filePath, int numberOfImages)
{
	std::cout << "Open file : " << filePath << std::endl;

	std::vector<std::vector<float>> images;

	std::ifstream file(filePath, std::ios::binary);

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
			abort();
		}

		int nbRows = 0;
		file.read((char*)&nbRows, 4);
		nbRows = ConvertToInt(nbRows);

		int nbColumns = 0;
		file.read((char*)&nbColumns, 4);
		nbColumns = ConvertToInt(nbColumns);

		int nbPixels = nbRows * nbColumns;

		images.resize(numberOfImages, std::vector<float>(nbPixels));

		for (int imageIdx = 0; imageIdx < numberOfImages; ++imageIdx)
		{
			for (int rowIdx = 0; rowIdx < nbRows; ++rowIdx)
			{
				for (int columnIdx = 0; columnIdx < nbColumns; ++columnIdx)
				{
					unsigned char pixelColor = 0;
					file.read((char*)&pixelColor, 1);
					images[imageIdx][(rowIdx * nbRows) + columnIdx] = (float)pixelColor;
				}
			}
		}

		file.close();
	}
	else
	{
		std::cout << "Can't open file : " << filePath << std::endl;
		abort();
	}

	return images;
}
std::vector<std::vector<float>> DataLoader::LoadLabels(std::string const& filePath, int numberOfLabels)
{
	std::cout << "Open file : " << filePath << std::endl;

	std::vector<std::vector<float>> labels;

	std::ifstream file(filePath, std::ios::binary);

	if (file.is_open())
	{
		int magicNumber = 0;
		file.read((char*)&magicNumber, 4);
		magicNumber = ConvertToInt(magicNumber);

		int nbLabels = 0;
		file.read((char*)&nbLabels, 4);
		nbLabels = ConvertToInt(nbLabels);

		if (nbLabels < numberOfLabels)
		{
			std::cout << "Not enough labels in file" << std::endl;
			abort();
		}

		labels.resize(numberOfLabels, std::vector<float>(10));

		for (int labelIdx = 0; labelIdx < numberOfLabels; ++labelIdx)
		{
			unsigned char label = 0;
			file.read((char*)&label, 1);
			labels[labelIdx] = VectorizeLabel((unsigned int)label);
		}

		file.close();
	}
	else
	{
		std::cout << "Can't open file : " << filePath << std::endl;
		abort();
	}

	return labels;
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
std::vector<float> DataLoader::VectorizeLabel(unsigned int value)
{
	std::vector<float> vectorizedLabel = std::vector<float>(10, 0);

	vectorizedLabel[value] = 1.f;

	return vectorizedLabel;
}
