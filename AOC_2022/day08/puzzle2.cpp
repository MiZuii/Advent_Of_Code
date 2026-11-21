#include "aoc_utils.h"
#include <functional>

int scenic_score(int sy, int sx, std::vector<std::string> &input)
{
    int res = 1;
    int base_h = static_cast<int>(input[sy][sx]) - static_cast<int>('0');
    int y, x;

    for(y=sy-1; y>=0; y--)
    {
        auto ch = static_cast<int>(input[y][sx]) - static_cast<int>('0');
        if(ch >= base_h) { y--; break; }
    }
    res *= abs(y-sy)-1;

    for(y=sy+1; y<input.size(); y++)
    {
        auto ch = static_cast<int>(input[y][sx]) - static_cast<int>('0');
        if(ch >= base_h) { y++; break; }
    }
    res *= abs(y-sy)-1;

    for(x=sx-1; x>=0; x--)
    {
        auto ch = static_cast<int>(input[sy][x]) - static_cast<int>('0');
        if(ch >= base_h) { x--; break; }
    }
    res *= abs(x-sx)-1;

    for(x=sx+1; x<input[0].size(); x++)
    {
        auto ch = static_cast<int>(input[sy][x]) - static_cast<int>('0');
        if(ch >= base_h) { x++; break; }
    }
    res *= abs(x-sx)-1;

    return res;
}

int solution(std::vector<std::string> &input)
{
    int res = 0;
    for( size_t x=1; x<input[0].size()-1; x++ )
    {
        for( size_t y=1; y<input.size()-1; y++ )
        {
            auto ss = scenic_score(y, x, input);
            if(ss > res) res = ss;        
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