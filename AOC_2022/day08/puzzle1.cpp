#include "aoc_utils.h"
#include <functional>

int solution(std::vector<std::string> &input)
{
    std::vector<std::vector<bool>> map(input.size());
    for( auto &v : map ) { v.resize(input[0].size()); }

    for( size_t x=0; x<input[0].size(); x++ )
    {
        int prev_height = -1;
        for( size_t y=0; y<input.size(); y++ )
        {
            auto new_height = static_cast<int>(input[y][x]) - static_cast<int>('0');
            if( new_height > prev_height )
            {
                map[y][x] = true;
                prev_height = new_height;
            }
        }
    }

    for( size_t y=0; y<input.size(); y++ )
    {
        int prev_height = -1;
        for( size_t x=0; x<input[0].size(); x++ )
        {
            auto new_height = static_cast<int>(input[y][x]) - static_cast<int>('0');
            if( new_height > prev_height )
            {
                map[y][x] = true;
                prev_height = new_height;
            }
        }
    }

    for( int x=input[0].size()-1; x>=0; x-- )
    {
        int prev_height = -1;
        for( int y=input.size()-1; y>=0; y-- )
        {
            auto new_height = static_cast<int>(input[y][x]) - static_cast<int>('0');
            if( new_height > prev_height )
            {
                map[y][x] = true;
                prev_height = new_height;
            }
        }
    }

    for( int y=input.size()-1; y>=0; y-- )
    {
        int prev_height = -1;
        for( int x=input[0].size()-1; x>=0; x-- )
        {
            auto new_height = static_cast<int>(input[y][x]) - static_cast<int>('0');
            if( new_height > prev_height )
            {
                map[y][x] = true;
                prev_height = new_height;
            }
        }
    }

    int res = 0;
    for( auto &v : map )
    {
        res += std::accumulate(v.begin(), v.end(), 0, [](int acc, const bool r) { if(r) return acc+1; return acc; });
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