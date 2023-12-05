#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <array>

std::array<uint32_t, 214> cards;
std::array<std::array<uint32_t, 214>, 214> done;
std::array<uint32_t, 214> winners;


uint32_t getTotalPart1(std::string filePath)
{
    std::string line;
    std::ifstream file(filePath);
    uint32_t i, start;
    std::set<uint32_t> winNums;
    uint32_t tot = 0;

    while (std::getline(file, line))
    {
        uint32_t lineTot = 0;
        winNums.clear();
        i = line.find(':') + 3;
        uint32_t end = i + 27;
        for (i; i <= end; i += 3)
        {
            uint32_t t = line[i] - 48;
            if (std::isdigit(line[i - 1]))
            {
                t += (line[i - 1] - 48) * 10;
            }
            winNums.insert(t);
        }

        i += 2;

        for (i; i < line.size(); i += 3)
        {
            uint32_t t = line[i] - 48;
            if (std::isdigit(line[i - 1]))
            {
                t += (line[i - 1] - 48) * 10;
            }

            if (winNums.find(t) != winNums.end())
            {
                if (lineTot != 0)
                {
                    lineTot = lineTot << 1;
                }
                else
                {
                    lineTot = 1;
                }
            }
        }
        tot += lineTot;
    }
    file.close();

    return tot;
}


// spent way too long on part 2 because i miss read it!!!

void helperPart2(uint32_t index)
{
    if (winners[index] == 0)
    {
        return;
    }

    // std::cout << "HERE\n";
    for (uint32_t i = index+1; i < index + winners[index] + 1; i++)
    {
        if (done[i][0] == -1)
        {
            std::array<uint32_t, 214> copy;
            std::copy(cards.begin(), cards.end(), copy.begin());
            cards[i]++;
            helperPart2(i);

            for (uint32_t j = 0; j < 214; j++)
            {
                done[i][j] = cards[j] - copy[j];
            }
        }
        else
        {
            for (uint32_t j = 0; j < 214; j++)
            {
                cards[j] += done[i][j];
            }
        }
    }
}

uint32_t getTotalPart2(std::string filePath)
{
    // two ways, just brute force it
    // or use memoization, go through list, brute force cards, if one cards cycle has been done before simple add those

    // we have three arrays, not what i want, but it makes
    // memoization easier,can optimise later
    std::string line;
    std::ifstream file(filePath);
    std::set<uint32_t> winNums;
    uint32_t total = 0;

    for (uint32_t i = 0; i < 214; i++)
    {
        cards[i] = 1;
        done[i][0] = -1;
    }

    uint32_t i, start;
    uint32_t index = 0;

    while (std::getline(file, line))
    {
        uint32_t tot = 0;
        winNums.clear();
        i = line.find(':') + 3;
        uint32_t end = i + 27;
        for (i; i <= end; i += 3)
        {
            uint32_t t = line[i] - 48;
            if (std::isdigit(line[i - 1]))
            {
                t += (line[i - 1] - 48) * 10;
            }
            winNums.insert(t);
        }

        i += 2;

        for (i; i < line.size(); i += 3)
        {
            uint32_t t = line[i] - 48;
            if (std::isdigit(line[i - 1]))
            {
                t += (line[i - 1] - 48) * 10;
            }

            if (winNums.find(t) != winNums.end())
            {
                tot++;
            }
        }
        winners[index] = tot;
        index++;
    }
    file.close();


    for (uint32_t i = 0; i < 214; i++)
    {
        helperPart2(i);
    }

    for (uint32_t i = 0; i < 214; i++)
    {
        total += cards[i];
    }

    return total;
}

int main()
{

    const std::string filePath = "./input.txt";
    std::cout << getTotalPart1(filePath) << "\n";
    std::cout << getTotalPart2(filePath);

    return 0;
}
