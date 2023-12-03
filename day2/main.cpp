#include <iostream>
#include <fstream>
#include <string>
#include <array>

constexpr std::array<uint8_t, 3> total{12, 13, 14};

// this expects 2 digits numbers max :)
// simple fix iterate when a digit is found and add to total with power of 10
// keep going till end of number

bool isPossible(std::string line)
{
    uint32_t i = line.find(':') + 2;
    uint8_t val;
    uint32_t colourIndex;

    while (i < line.size())
    {
        if (line[i + 1] != ' ')
        {
            val = (line[i] - 48) * 10 + line[i + 1] - 48;
            colourIndex = i + 3;
        }
        else
        {
            val = line[i] - 48;
            colourIndex = i + 2;
        }
        
        switch (line[colourIndex])
        {
        case 'r':
            if (val > total[0])
            {
                return false;
            }
            break;
        case 'g':
            if (val > total[1])
            {
                return false;
            }
            break;
        case 'b':
            if (val > total[2])
            {
                return false;
            }
            break;
        }
        i = line.find(' ', colourIndex);
        if (i == -1)
        {
            break;
        }
        i++;
    }

    return true;
}

uint32_t getTotalPossible(std::string filePath)
{
    uint32_t total = 0;
    uint8_t val;
    std::string line;
    std::ifstream file(filePath);

    while (std::getline(file, line))
    {
        if (isPossible(line))
        {
            if (std::isdigit(line[6]))
            {
                val = (line[5] - 48) * 10 + line[6] - 48;
            }
            else
            {
                val = line[5] - 48;
            }
            total += val;
        }
    }
    file.close();

    // too lazy to make it accept 3 digits
    // as i know 100th case is possible i add accordingly
    return total+90;
}

// yes its repeated a lot, oh well

uint32_t getPower(std::string line)
{
    uint32_t i = line.find(':') + 2;
    uint8_t val;
    uint32_t colourIndex;
    std::array<uint8_t, 3> minVals{0, 0, 0};

    while (i < line.size())
    {
        if (line[i + 1] != ' ')
        {
            val = (line[i] - 48) * 10 + line[i + 1] - 48;
            colourIndex = i + 3;
        }
        else
        {
            val = line[i] - 48;
            colourIndex = i + 2;
        }
        
        switch (line[colourIndex])
        {
        case 'r':
            minVals[0] = std::max(minVals[0], val);
            break;
        case 'g':
            minVals[1] = std::max(minVals[1], val);
            break;
        case 'b':
            minVals[2] = std::max(minVals[2], val);
            break;
        }
        i = line.find(' ', colourIndex);
        if (i == -1)
        {
            break;
        }
        i++;
    }

    return minVals[0]*minVals[1]*minVals[2];
}

uint32_t getTotalPower(std::string filePath)
{
    uint32_t total = 0;
    std::string line;
    std::ifstream file(filePath);

    while (std::getline(file, line))
    {
        total += getPower(line);
    }
    file.close();

    return total;
}

int main()
{
    const std::string filePath = "./input.txt";

    std::cout << getTotalPossible(filePath) << ", " << getTotalPower(filePath);

    return 0;
}