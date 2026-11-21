#include "aoc_utils.h"

int solution(std::vector<std::string> &input)
{
    int x=1;
    int ic=0;
    int res=0;

    for( auto &l : input )
    {
        if( l.substr(0, 4) == "noop" )
        {
            ic++;
            if( ic >= 20 && (ic - 20) % 40 == 0 )
            {
                res += ic * x;
            }
        }
        else
        {
            int v = std::stoi(l.substr(5));
            ic++;
            if( ic >= 20 && (ic - 20) % 40 == 0 )
            {
                res += ic * x;
            }
            ic++;
            if( ic >= 20 && (ic - 20) % 40 == 0 )
            {
                res += ic * x;
            }
            x += v;
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