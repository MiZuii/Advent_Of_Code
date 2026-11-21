#include "aoc_utils.h"

std::string solution(std::vector<std::string> &input)
{
    int stacks_num = (input[0].size()+1)/4;
    size_t stacks_max_height = 0;
    std::vector<std::vector<char>> stacks;
    for( ; stacks_max_height<input.size(); stacks_max_height++ )
    {
        if(input[stacks_max_height].empty()) break;
    }
    stacks_max_height--;

    for( int x=0; x<stacks_num; x++ )
    {
        stacks.push_back({});
        for( int y=stacks_max_height-1; y>=0; y-- )
        {
            if(input[y][x*4+1] == ' ') break;
            stacks.back().push_back(input[y][x*4+1]);
        }
    }

    for( size_t y=stacks_max_height+2; y<input.size(); y++)
    {
        auto fs = aoc::split(input[y].substr(4), " from ");
        int quant = std::stoi(fs[0]);
        auto ss = aoc::split(fs[1], " to ");
        int from = std::stoi(ss[0])-1;
        int to = std::stoi(ss[1])-1;

        for( auto i=0; i<quant; i++)
        {
            stacks[to].push_back(stacks[from].back());
            stacks[from].pop_back();
        }
    }

    return std::accumulate(
        stacks.begin(),
        stacks.end(),
        std::string(),
        [](std::string acc, const std::vector<char> &r)
            {return acc + r.back();});
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