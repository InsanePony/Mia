#pragma once

#include <vector>
#include <iostream>

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
