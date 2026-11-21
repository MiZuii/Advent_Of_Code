#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

int solution(std::vector<std::string> &input)
{
    int psum = 0;
    std::vector<int> maxv;

    for( auto line : input )
    {
        if(line.empty())
        {
            maxv.push_back(psum);
            if( maxv.size() > 3 )
            {
                std::sort(maxv.begin(), maxv.end());
                maxv.erase(maxv.begin());
            }

            psum = 0;
            continue;
        }

        psum += stoi(line);
    }

    return std::accumulate(maxv.begin(), maxv.end(), 0);
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
