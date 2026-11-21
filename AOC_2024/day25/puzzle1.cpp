#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <array>

bool matches(std::array<int, 5> &key, std::array<int, 5> &lock)
{
    for( size_t i=0; i<5; i++ )
    {
        if(key[i] + lock[i] > 5) return false;
    }
    return true;
}

int solution(std::vector<std::string> &input)
{
    int res = 0;
    std::vector<std::array<int, 5>> locks;
    std::vector<std::array<int, 5>> keys;
    for( size_t ys=0; ys<input.size()-6; ys += 8)
    {
        if(input[ys][0] == '#')
        {
            keys.push_back(std::array<int, 5>());
            for( size_t x=0; x<5; x++ )
            {
                size_t y=0;
                for( ; y<7; y++ )
                {
                    if(input[ys+y][x] == '.') break;
                }
                keys.back()[x] = y-1;
            }
        }
        else
        {
            locks.push_back(std::array<int, 5>());
            for( size_t x=0; x<5; x++ )
            {
                size_t y=6;
                for( ; y >= 0; y-- )
                {
                    if(input[ys+y][x] == '.') break;
                }
                locks.back()[x] = 5-y;
            }
        }
    }

    for( auto &key : keys )
    {
        for( auto &lock : locks )
        {
            if( matches(key, lock) ) res++;
        }
    }

    return res;
}

int main(int argc, char* argv[]) {
    std::string inputFilename = "input.txt";

    std::ifstream inputFile(inputFilename);
    if (!inputFile) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    std::vector<std::string> input;
    std::string line;
    while (std::getline(inputFile, line)) {
        input.push_back(line);
    }
    inputFile.close();

    std::cout << solution(input) << std::endl;
    return 0;
}
