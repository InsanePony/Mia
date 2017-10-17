#pragma once

#include <vector>
#include <iostream>

struct Utility
{
	template <typename T>
	static std::vector<T> Transpose(std::vector<T> const& vector, unsigned int nbRow, unsigned int nbColumn)
	{
		unsigned int totalSize = nbRow * nbColumn;
		if (totalSize != vector.size())
		{
			std::cout << "Error in Transpose : given row or column is incorrect" << std::endl;
			abort();
		}

		std::vector<T> result;
		result.resize(totalSize);

		for (unsigned int idx = 0; idx < totalSize; ++idx)
		{
			int columnIdx = idx / nbRow;
			int rowIdx = idx % nbRow;

			result[idx] = vector[rowIdx * nbColumn + columnIdx];
		}

		return result;
	}
};

template <typename T>
std::vector<T> operator - (std::vector<T> const& a, std::vector<T> const& b)
{
	if (a.size() != b.size())
	{
		std::cout << "Error in std::vector<T> operator - (std::vector<T> const& a, std::vector<T> const& b) : different size" << std::endl;
		abort();
	}

	std::vector<T> result;

	size_t size = a.size();
	result.resize(size);

	for (size_t idx = 0; idx < size; ++idx)
		result[idx] = a[idx] - b[idx];

	return result;
}

template <typename T>
std::vector<T> operator * (std::vector<T> const& vector, T value)
{
	std::vector<T> result;

	size_t size = vector.size();
	result.resize(size);

	for (size_t idx = 0; idx < size; ++idx)
		result[idx] = vector[idx] * value;

	return result;
}
