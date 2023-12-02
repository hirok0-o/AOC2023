#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::map<std::string, int> digitMap = {
	{"zero", 0},
	{"one", 1},
	{"two", 2},
	{"three", 3},
	{"four", 4},
	{"five", 5},
	{"six", 6},
	{"seven", 7},
	{"eight", 8},
	{"nine", 9}};

uint8_t subStringValue(std::string line, bool dir, int index)
{
	std::string key;

	for (uint8_t i = 3; i < 6; i++)
	{
		if (dir == 1)
		{
			if (index + i > line.length())
			{
				break;
			}
			key = line.substr(index, i);
		}
		else
		{
			if (index - i < 0)
			{
				break;
			}
			key = line.substr(index - i, i);
		}
		if (digitMap.find(key) != digitMap.end())
		{
			return digitMap[key];
		}
	}

	return -1;
}

uint8_t getNumber(std::string line)
{
	size_t left = 0;
	size_t right = line.length();
	uint8_t leftVal = -1;
	uint8_t rightVal = -1;
	uint8_t tempVal;
	bool foundLeft = false;
	bool foundRight = false;

	while (!foundLeft || !foundRight)
	{
		if (!foundLeft)
		{
			if (std::isdigit(line[left]))
			{
				leftVal = (line[left] - 48) * 10;
				foundLeft = true;
			}
			tempVal = subStringValue(line, 1, left);
			if (tempVal != -1)
			{
				leftVal = tempVal * 10;
				foundLeft = true;
			}
			left++;
		}
		if (!foundRight)
		{
			if (std::isdigit(line[right]))
			{
				rightVal = line[right] - 48;
				foundRight = true;
			}
			tempVal = subStringValue(line, 0, right);
			if (!foundRight && tempVal != -1)
			{
				rightVal = tempVal;
				foundRight = true;
			}
			right--;
		}

	}

	return leftVal + rightVal;
}

uint16_t getTotal(std::string filePath)
{
	uint16_t total = 0;
	std::string line;
	std::ifstream file(filePath);

	while (std::getline(file, line))
	{
		total += getNumber(line);
	}

	return total;
}

int main()
{
	const std::string filePath = "./input.txt";
	std::cout << getTotal(filePath);
	return 0;
}
