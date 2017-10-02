#include "DataLoader.h"

int DataLoader::ConvertToInt(int value)
{
	unsigned char c1, c2, c3, c4;

	c1 = value & 255;
	c2 = (value >> 8) & 255;
	c3 = (value >> 16) & 255;
	c4 = (value >> 24) & 255;

	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}
