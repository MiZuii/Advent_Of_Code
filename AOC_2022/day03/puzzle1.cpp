#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_set>
#include <cctype>

int solution(std::vector<std::string> &input)
{
    int res = 0;
    for( auto rucsac : input )
    {
        auto compartment1 = rucsac.substr(0, rucsac.size()/2);
        auto compartment2 = rucsac.substr(rucsac.size()/2, rucsac.size()/2);
        std::unordered_set<char> cp1_set(compartment1.begin(), compartment1.end());
        for( auto c : compartment2 )
        {
            if( cp1_set.find(c) != cp1_set.end() )
            {
                if( std::islower(c) ) res += (int)c - (int)'a' + 1;
                else res += (int)c - (int)'A' + 27;
                break;
            }
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
