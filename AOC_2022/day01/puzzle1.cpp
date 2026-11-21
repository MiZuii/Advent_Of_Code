#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>

int solution(std::vector<std::string> &input)
{
    int psum = 0;
    int maxs = 0;

    for( auto line : input )
    {
        if(line.empty())
        {
            maxs = std::max(maxs, psum);
            psum = 0;
            continue;
        }

        psum += stoi(line);
    }

    return maxs;
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
