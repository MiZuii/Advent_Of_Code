#include "aoc_utils.h"

std::string solution(std::vector<std::string> &input)
{
    int x=1;
    int ic=0;
    std::string res;

    for( auto &l : input )
    {
        if( l.substr(0, 4) == "noop" )
        {
            if( ic % 40 >= x-1 && ic % 40 <= x+1 ) res += "#";
            else res += ".";
            ic++;
        }
        else
        {
            int v = std::stoi(l.substr(5));
            if( ic % 40 >= x-1 && ic % 40 <= x+1 ) res += "#";
            else res += ".";
            ic++;
            if( ic % 40 >= x-1 && ic % 40 <= x+1 ) res += "#";
            else res += ".";
            ic++;
            x += v;
        }
    }
    for(int i=1; i<=5; i++)
    {
        res.insert(40*i-1+i, 1, '\n');
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