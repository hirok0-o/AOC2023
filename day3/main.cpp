#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <string>
#include <map>
#include <vector>

bool isAdjacent(const std::array<std::string, 140> *arr, int i, int j, int k)
{
    for (int jIndex = j - 1; jIndex <= k; jIndex++)
    {
        if ((jIndex >= 0 && jIndex < 140))
        {
            if (i - 1 >= 0)
            {
                if ((*arr)[i - 1][jIndex] != '.' && !std::isdigit((*arr)[i - 1][jIndex]))
                {
                    return true;
                }
            }
            if (i + 1 < 140)
            {
                if ((*arr)[i + 1][jIndex] != '.' && !std::isdigit((*arr)[i + 1][jIndex]))
                {
                    return true;
                }
            }
        }
    }
    if (j - 1 >= 0)
    {
        if ((*arr)[i][j - 1] != '.' && !std::isdigit((*arr)[i][j - 1]))
        {
            return true;
        }
    }

    if (k < 140)
    {
        if ((*arr)[i][k] != '.' && !std::isdigit((*arr)[i][k]))
        {
            return true;
        }
    }

    return false;
}

std::array<std::string, 140> fileToArray(std::string filePath)
{
    std::array<std::string, 140> arr;
    std::string line;
    std::ifstream file(filePath);
    int i = 0;

    while (std::getline(file, line))
    {
        arr[i] = line;
        i++;
    }
    file.close();

    return arr;
}

int getTotal(const std::array<std::string, 140> *arr)
{
    // iterate through, find groups of digits
    int j, k, kCopy;
    int pow;
    int tot = 0;

    for (int i = 0; i < 140; i++)
    {
        j = 0;
        while (j < 141)
        {

            // find where the digit ends
            if (std::isdigit((*arr)[i][j]))
            {
                k = j;
                while (k < 141 && std::isdigit((*arr)[i][k]))
                {
                    k++;
                }
                k = std::min(k, 140);
                if (isAdjacent(arr, i, j, k))
                {
                    pow = 1;
                    kCopy = k - 1;
                    while (kCopy >= j)
                    {
                        tot += ((*arr)[i][kCopy] - 48) * pow;
                        pow *= 10;
                        kCopy--;
                    }
                }
                j = k + 1;
            }
            else
            {
                j++;
            }
        }
    }

    return tot;
}


std::array<int, 2> adjacentGear(const std::array<std::string, 140> *arr, int i, int j, int k){

    for (int jIndex = j - 1; jIndex <= k; jIndex++)
    {
        if ((jIndex >= 0 && jIndex < 140))
        {
            if (i - 1 >= 0)
            {
                if ((*arr)[i - 1][jIndex] == '*')
                {
                    return {i-1, jIndex};
                }
            }
            if (i + 1 < 140)
            {
                if ((*arr)[i + 1][jIndex] == '*')
                {
                    return {i+1, jIndex};
                }
            }
        }
    }
    if (j - 1 >= 0)
    {
        if ((*arr)[i][j - 1] == '*')
        {
            return {i, j-1};
        }
    }

    if (k < 140)
    {
        if ((*arr)[i][k] == '*')
        {
            return {i, k};
        }
    }

    return {-1, -1};
}


int getGearRation(const std::array<std::string, 140> *arr)
{

    // iterate through, find groups of digits
    int j, k, kCopy;
    int pow;
    int tot = 0;
    int val;
    std::array<int, 2> gear;
    std::map<std::array<int, 2>, std::vector<int>> gears;

    for (int i = 0; i < 140; i++)
    {
        j = 0;
        while (j < 141)
        {

            // find where the digit ends
            if (std::isdigit((*arr)[i][j]))
            {
                k = j;
                while (k < 141 && std::isdigit((*arr)[i][k]))
                {
                    k++;
                }
                k = std::min(k, 140);

                gear = adjacentGear(arr, i, j, k);

                if (gear != std::array<int, 2>{-1, -1})
                {
                    val = 0;
                    pow = 1;
                    kCopy = k - 1;
                    while (kCopy >= j)
                    {
                        val += ((*arr)[i][kCopy] - 48) * pow;
                        pow *= 10;
                        kCopy--;
                    }
                    gears[gear].push_back(val);

                    if (gears[gear].size() == 2){
                        tot += gears[gear][0]*gears[gear][1];
                    }
                }
                j = k + 1;
            }
            else
            {
                j++;
            }
        }
    }

    return tot;
}

int main()
{
    const std::string filePath = "./input.txt";

    std::array<std::string, 140> arr = fileToArray(filePath);

    std::cout << getGearRation(&arr);

    return 0;
}
